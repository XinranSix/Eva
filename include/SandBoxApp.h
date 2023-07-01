/**
 * @file    :   SandBoxApp.h
 * @date    :   2023/06/27 14:48:18
 * @author  :   yaojie
 * @version :   1.0
 */

#pragma once

#include <glm/glm.hpp>

#include "Layer.h"
#include "Log.h"
#include "LayerStack.h"
#include "Input.h"
#include "KeyCodes.h"
#include "Event.h"
#include "ApplicationEvent.h"
#include "KeyEvent.h"
#include "imgui.h"
#include "Window.h"
#include "eva/eva.h"
#include "ApplicationEvent.h"
#include "Layer.h"
#include "LayerStack.h"
#include "ImGuiLayer.h"
#include "Shader.h"
#include "Buffer.h"
#include "VertexArray.h"
#include "OrthographicCamera.h"
#include "Application.h"
#include "SandBoxApp.h"
#include "eva/Assert.h"
#include "Renderer.h"
#include "RenderCommand.h"
#include "Event.h"

// FIXME:示例 Layer
class ExampleLayer : public Eva::Layer {
public:
    ExampleLayer()
        : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f),
          m_CameraPosition(0.0f) {

        m_VertexArray.reset(Eva::VertexArray::Create());

        float vertices[] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, //
            0.5f,  -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, //
            0.0f,  0.5f,  0.0f, 1.0f, 1.0f, 0.0f  //
        };

        std::shared_ptr<Eva::VertexBuffer> m_VertexBuffer;
        m_VertexBuffer.reset(
            Eva::VertexBuffer::Create(vertices, sizeof(vertices)));

        Eva::BufferLayout layout = {
            {Eva::ShaderDataType::Float3, "a_Position"},
            {Eva::ShaderDataType::Float3, "a_Color"},
        };
        m_VertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(m_VertexBuffer);

        uint32_t indices[3] = {0, 1, 2};

        std::shared_ptr<Eva::IndexBuffer> m_IndexBuffer;
        m_IndexBuffer.reset(Eva::IndexBuffer::Create(
            indices, sizeof(indices) / sizeof(uint32_t)));

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

        m_Shader.reset(new Eva::Shader(vertexSrc, fragmentSrc));

        m_SquareVA.reset(Eva::VertexArray::Create());

        float squareVertices[] = {
            -0.75f, -0.75f, 0.0f, //
            0.75f,  -0.75f, 0.0f, //
            0.75f,  0.75f,  0.0f, //
            -0.75f, 0.75f,  0.0f  //
        };

        std::shared_ptr<Eva::VertexBuffer> squareVB;
        squareVB.reset(
            Eva::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

        squareVB->SetLayout({{Eva::ShaderDataType::Float3, "a_Position"}});
        m_SquareVA->AddVertexBuffer(squareVB);

        uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
        std::shared_ptr<Eva::IndexBuffer> squareIB;
        squareIB.reset(Eva::IndexBuffer::Create(
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
            new Eva::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
    }

    void OnUpdate(Eva::Timestep ts) override {
        // FIXME: 方向似乎不对
        if (Eva::Input::IsKeyPressed(EVA_KEY_LEFT)) {
            m_CameraPosition.x -= m_CameraMoveSpeed * ts;
        } else if (Eva::Input::IsKeyPressed(EVA_KEY_RIGHT)) {
            m_CameraPosition.x += m_CameraMoveSpeed * ts;
        }

        if (Eva::Input::IsKeyPressed(EVA_KEY_UP)) {
            m_CameraPosition.y += m_CameraMoveSpeed * ts;
        } else if (Eva::Input::IsKeyPressed(EVA_KEY_DOWN)) {
            m_CameraPosition.y -= m_CameraMoveSpeed * ts;
        }

        if (Eva::Input::IsKeyPressed(EVA_KEY_A)) {
            m_CameraRotation += m_CameraRotationSpeed * ts;
        } else if (Eva::Input::IsKeyPressed(EVA_KEY_D)) {
            m_CameraRotation -= m_CameraRotationSpeed * ts;
        }

        Eva::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.00f});
        Eva::RenderCommand::Clear();

        m_Camera.SetPosition(m_CameraPosition);
        m_Camera.SetRotation(m_CameraRotation);

        Eva::Renderer::BeginScene(m_Camera);
        Eva::Renderer::Submit(m_BlueShader, m_SquareVA);
        Eva::Renderer::Submit(m_Shader, m_VertexArray);

        Eva::Renderer::EndScene();
    }

    void OnImGuiRender() override {}

    void OnEvent(Eva::Event &event) override {}

private:
    std::shared_ptr<Eva::Shader> m_Shader;
    std::shared_ptr<Eva::VertexArray> m_VertexArray;

    std::shared_ptr<Eva::Shader> m_BlueShader;
    std::shared_ptr<Eva::VertexArray> m_SquareVA;

    Eva::OrthographicCamera m_Camera;
    glm::vec3 m_CameraPosition;
    float m_CameraMoveSpeed = 1.0f;
    float m_CameraRotation = 0.0f;
    float m_CameraRotationSpeed = 30.0f;
};

class SandBox : public Eva::Application {
public:
    SandBox();

    ~SandBox();
};
