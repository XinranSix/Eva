/**
 * @file    :   Application.cpp
 * @date    :   2023/06/27 14:55:38
 * @author  :   yaojie
 * @version :   1.0
 */

#include <glad/glad.h>
// #include <GLFW/glfw3.h>
#include <memory>
#include <stdint.h>
#include <vcruntime.h>

#include "Application.h"
#include "SandBoxApp.h"
#include "eva/Assert.h"
// #include "ApplicationEvent.h"
// #include "Log.h"
// #include "Input.h"

// class SandBox;

namespace Eva {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

    Application *Application::s_Instance = nullptr;

    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
        switch (type) {
        case ShaderDataType::Float:
            return GL_FLOAT;
        case ShaderDataType::Float2:
            return GL_FLOAT;
        case ShaderDataType::Float3:
            return GL_FLOAT;
        case ShaderDataType::Float4:
            return GL_FLOAT;
        case ShaderDataType::Mat3:
            return GL_FLOAT;
        case ShaderDataType::Mat4:
            return GL_FLOAT;
        case ShaderDataType::Int:
            return GL_INT;
        case ShaderDataType::Int2:
            return GL_INT;
        case ShaderDataType::Int3:
            return GL_INT;
        case ShaderDataType::Int4:
            return GL_INT;
        case ShaderDataType::Bool:
            return GL_BOOL;
        }
        EVA_CORE_ASSERT(false, "UnKnown ShaderDataType!");
        return 0;
    }

    Application::Application() {
        EVA_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

        glGenVertexArrays(1, &m_VertexArray);
        glBindVertexArray(m_VertexArray);

        float vertices[] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, //
            0.5f,  -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, //
            0.0f,  0.5f,  0.0f, 1.0f, 1.0f, 0.0f  //
        };

        // float vertices[] = {
        //     -0.5f, -0.5f, 0.0f, //
        //     0.5f,  -0.5f, 0.0f, //
        //     0.0f,  0.5f,  0.0f, //
        // };

        m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

        {
            BufferLayout layout = {
                {ShaderDataType::Float3, "a_Position"},
                {ShaderDataType::Float3, "a_Color"},
            };
            m_VertexBuffer->SetLayout(layout);
        }

        uint32_t index = 0;
        // FIXME: 此处有 Bug，layout 不能是 const 修饰的，不知道为什么
        // const auto &layout = m_VertexBuffer->GetLayout();
        auto layout = m_VertexBuffer->GetLayout();

        for (const auto &element : layout) {
            std::cout << element.Name << std::endl;
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, element.GetComponentCount(),
                                  ShaderDataTypeToOpenGLBaseType(element.Type),
                                  element.Normalized ? GL_TRUE : GL_FALSE,
                                  layout.GetStride(),
                                  (const void *)element.Offset);
            ++index;
        }

        uint32_t indices[3] = {0, 1, 2};
        m_IndexBuffer.reset(
            IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

        std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec3 a_Color;

            out vec3 v_Color;
            out vec3 v_Position;

            void main() {
                gl_Position = vec4(a_Position, 1.0);
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
        // HZ_PROFILE_FUNCTION();
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer *layer) {
        // HZ_PROFILE_FUNCTION();
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::Run() {
        while (m_Running) {

            glClearColor(0.1f, 0.1f, 0.1f, 1.00f);
            glClear(GL_COLOR_BUFFER_BIT);

            m_Shader->Bind();
            glBindVertexArray(m_VertexArray);
            glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(),
                           GL_UNSIGNED_INT, nullptr);

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
