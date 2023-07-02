/**
 * @file    :   SandBoxApp.h
 * @date    :   2023/06/27 14:48:18
 * @author  :   Yao J
 * @version :   1.0
 */

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

#include "Application.h"
#include "SandBoxApp.h"
#include "Renderer.h"
#include "Log.h"
#include "Input.h"
#include "ApplicationEvent.h"
#include "KeyCodes.h"
#include "OpenGLShader.h"
#include "Texture.h"

// FIXME:示例 Layer
class ExampleLayer : public Eva::Layer {
public:
    ExampleLayer()
        : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f),
          m_CameraPosition(0.0f), m_SquarePosition(0.0f) {

        m_VertexArray.reset(Eva::VertexArray::Create());

        float vertices[] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, //
            0.5f,  -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, //
            0.0f,  0.5f,  0.0f, 1.0f, 1.0f, 0.0f  //
        };

        Eva::Ref<Eva::VertexBuffer> m_VertexBuffer;
        m_VertexBuffer.reset(
            Eva::VertexBuffer::Create(vertices, sizeof(vertices)));

        Eva::BufferLayout layout = {
            {Eva::ShaderDataType::Float3, "a_Position"},
            {Eva::ShaderDataType::Float3, "a_Color"},
        };
        m_VertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(m_VertexBuffer);

        uint32_t indices[3] = {0, 1, 2};

        Eva::Ref<Eva::IndexBuffer> m_IndexBuffer;
        m_IndexBuffer.reset(Eva::IndexBuffer::Create(
            indices, sizeof(indices) / sizeof(uint32_t)));

        m_VertexArray->SetIndexBuffer(m_IndexBuffer);

        std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec3 a_Color;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            out vec3 v_Color;
            out vec3 v_Position;

            void main() {
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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

        m_Shader.reset(Eva::Shader::Create(vertexSrc, fragmentSrc));

        m_SquareVA.reset(Eva::VertexArray::Create());

        float squareVertices[] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, //
            0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, //
            0.5f,  0.5f,  0.0f, 1.0f, 1.0f, //
            -0.5f, 0.5f,  0.0f, 0.0f, 1.0f  //
        };

        Eva::Ref<Eva::VertexBuffer> squareVB;
        squareVB.reset(
            Eva::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

        squareVB->SetLayout({{Eva::ShaderDataType::Float3, "a_Position"},
                             {Eva::ShaderDataType::Float2, "a_TexCoord"}});

        m_SquareVA->AddVertexBuffer(squareVB);

        uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
        Eva::Ref<Eva::IndexBuffer> squareIB;
        squareIB.reset(Eva::IndexBuffer::Create(
            squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        m_SquareVA->SetIndexBuffer(squareIB);

        std::string flatColorShaderVertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            void main() {
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
            }
        )";

        std::string flatColorShaderFragmentSrc = R"(
            #version 330 core

            out vec4 color;

            uniform vec3 u_Color;

            void main() {
                color = vec4(u_Color, 1.0);
            }
        )";

        m_FlatColorShader.reset(Eva::Shader::Create(
            flatColorShaderVertexSrc, flatColorShaderFragmentSrc));

        std::string textureShaderVertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec2 a_TexCoord;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            out vec2 v_TexCoord;

            void main() {
                v_TexCoord = a_TexCoord;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
            }
        )";

        std::string textureShaderFragmentSrc = R"(
            #version 330 core

            in vec2 v_TexCoord;

            out vec4 color;

            uniform sampler2D u_Texture;

            void main() {
                color = texture(u_Texture, v_TexCoord);
            }
        )";

        m_TextureShader.reset(Eva::Shader::Create(textureShaderVertexSrc,
                                                  textureShaderFragmentSrc));

        m_Texture =
            Eva::Texture2D::Create("./assets/textures/Checkerboard.png");

        m_ChernoLogTexture =
            Eva::Texture2D::Create("./assets/textures/ChernoLogo.png");

        std::dynamic_pointer_cast<Eva::OpenGLShader>(m_TextureShader)->Bind();
        std::dynamic_pointer_cast<Eva::OpenGLShader>(m_TextureShader)
            ->UploadUniformInt("u_Texture", 0);
    }

    void OnUpdate(Eva::Timestep ts) override {

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

        if (Eva::Input::IsKeyPressed(EVA_KEY_J)) {
            m_SquarePosition.x -= m_SquareMoveSpeed * ts;
        } else if (Eva::Input::IsKeyPressed(EVA_KEY_L)) {
            m_SquarePosition.x += m_SquareMoveSpeed * ts;
        }

        if (Eva::Input::IsKeyPressed(EVA_KEY_I)) {
            m_SquarePosition.y += m_SquareMoveSpeed * ts;
        } else if (Eva::Input::IsKeyPressed(EVA_KEY_K)) {
            m_SquarePosition.y -= m_SquareMoveSpeed * ts;
        }

        Eva::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.00f});
        Eva::RenderCommand::Clear();

        m_Camera.SetPosition(m_CameraPosition);
        m_Camera.SetRotation(m_CameraRotation);

        Eva::Renderer::BeginScene(m_Camera);

        static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

        std::dynamic_pointer_cast<Eva::OpenGLShader>(m_FlatColorShader)->Bind();
        std::dynamic_pointer_cast<Eva::OpenGLShader>(m_FlatColorShader)
            ->UploadUniformFloat3("u_Color", m_SquareColor);

        for (int y = 0; y < 20; ++y) {
            for (int x = 0; x < 20; x++) {
                glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
                glm::mat4 transform =
                    glm::translate(glm::mat4(1.0f), pos) * scale;
                Eva::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
            }
        }

        m_Texture->Bind();
        Eva::Renderer::Submit(m_TextureShader, m_SquareVA,
                              glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
        m_ChernoLogTexture->Bind();
        Eva::Renderer::Submit(m_TextureShader, m_SquareVA,

                              glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        Eva::Renderer::EndScene();
    }

    void OnImGuiRender() override {
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
        ImGui::End();
    }

    void OnEvent(Eva::Event &event) override {}

private:
    Eva::Ref<Eva::Shader> m_Shader;
    Eva::Ref<Eva::VertexArray> m_VertexArray;

    Eva::Ref<Eva::Shader> m_FlatColorShader, m_TextureShader;
    Eva::Ref<Eva::VertexArray> m_SquareVA;

    Eva::Ref<Eva::Texture2D> m_Texture, m_ChernoLogTexture;

    Eva::OrthographicCamera m_Camera;
    glm::vec3 m_CameraPosition;

    float m_CameraMoveSpeed = 5.0f;
    float m_CameraRotation = 0.0f;
    float m_CameraRotationSpeed = 180.0f;

    glm::vec3 m_SquarePosition;
    float m_SquareMoveSpeed = 1.0f;

    glm::vec3 m_SquareColor = {0.2f, 0.3f, 0.8f};
};

class SandBox : public Eva::Application {
public:
    SandBox();

    ~SandBox();
};
