/**
 * @file    :   Application.cpp
 * @date    :   2023/06/27 14:55:38
 * @author  :   yaojie
 * @version :   1.0
 */

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <stdint.h>
#include <vcruntime.h>

#include "Application.h"
#include "SandBoxApp.h"
#include "eva/Assert.h"
#include "Renderer.h"
#include "OrthographicCamera.h"

namespace Eva {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

    Application *Application::s_Instance = nullptr;

    Application::Application() : m_Camera(-1.6f, 1.6f, -0.9f, 0.9f) {
        EVA_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

        m_VertexArray.reset(VertexArray::Create());

        float vertices[] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, //
            0.5f,  -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, //
            0.0f,  0.5f,  0.0f, 1.0f, 1.0f, 0.0f  //
        };

        std::shared_ptr<VertexBuffer> m_VertexBuffer;
        m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

        BufferLayout layout = {
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float3, "a_Color"},
        };
        m_VertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(m_VertexBuffer);

        uint32_t indices[3] = {0, 1, 2};

        std::shared_ptr<IndexBuffer> m_IndexBuffer;
        m_IndexBuffer.reset(
            IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

        m_VertexArray->SetIndexBuffer(m_IndexBuffer);

        std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec3 a_Color;

            uniform mat4 u_ViewProjection;

            out vec3 v_Color;
            out vec3 v_Position;

            void main() {
                gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
                v_Color = a_Color;
                v_Position = a_Position;
            }
        )";

        std::string fragmentSrc = R"(
            #version 330 core

            in vec3 v_Position;
            in vec3 v_Color;

            out vec4 color;

            void main() {
                color =vec4(v_Color, 1.0);
            }
        )";

        m_Shader.reset(new Shader(vertexSrc, fragmentSrc));

        m_SquareVA.reset(VertexArray::Create());

        float squareVertices[] = {
            -0.75f, -0.75f, 0.0f, //
            0.75f,  -0.75f, 0.0f, //
            0.75f,  0.75f,  0.0f, //
            -0.75f, 0.75f,  0.0f  //
        };

        std::shared_ptr<VertexBuffer> squareVB;
        squareVB.reset(
            VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

        squareVB->SetLayout({{ShaderDataType::Float3, "a_Position"}});
        m_SquareVA->AddVertexBuffer(squareVB);

        uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
        std::shared_ptr<IndexBuffer> squareIB;
        squareIB.reset(IndexBuffer::Create(
            squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        m_SquareVA->SetIndexBuffer(squareIB);

        std::string blueShaderVertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;

            uniform mat4 u_ViewProjection;

            void main() {
                gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
            }
        )";

        std::string blueShaderFragmentSrc = R"(
            #version 330 core

            out vec4 color;

            // uniform vec3 u_Color;

            void main() {
                color =vec4(1.0,1.0,0.0, 1.0);
            }
        )";

        m_BlueShader.reset(
            new Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
    }

    Application::~Application() {}

    void Application::OnEvent(Event &e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(
            BIND_EVENT_FN(Application::OnWindownClose));

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
            (*--it)->OnEvent(e);
            if (e.Handled) {
                break;
            }
        }
    }

    void Application::PushLayer(Layer *layer) {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer *layer) {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::Run() {
        while (m_Running) {

            RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.00f});
            RenderCommand::Clear();

            m_Camera.SetPosition({0.5f, 0.5f, 0.0f});
            m_Camera.SetRotation(45.0f);

            Renderer::BeginScene(m_Camera);
            Renderer::Submit(m_BlueShader, m_SquareVA);
            Renderer::Submit(m_Shader, m_VertexArray);

            Renderer::EndScene();

            for (Layer *layer : m_LayerStack) {
                layer->OnUpdate();
            }

            m_ImGuiLayer->Begin();
            for (Layer *layer : m_LayerStack) {
                layer->OnImGuiRender();
            }
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindownClose(WindowCloseEvent &e) {
        m_Running = false;
        return true;
    }

    Eva::Application *CreateApplication() { return new SandBox(); }
} // namespace Eva
