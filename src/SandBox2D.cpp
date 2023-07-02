/**
 * @file    :   SandBox2D.cpp
 * @date    :   2023/07/02 19:07:27
 * @author  :   Yao J
 * @version :   1.0
 */

#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Renderer.h"
#include "SandBox2D.h"
#include "RenderCommand.h"
#include "OpenGLShader.h"

SandBox2D::SandBox2D()
    : Layer("SandBox2D"), m_CameraController(1280.0f / 720.f) {}

void SandBox2D::OnAttach() {

    m_SquareVA = Eva::VertexArray::Create();

    float squareVertices[3 * 4] = {
        -0.5f, -0.5f, 0.0f, //
        0.5f,  -0.5f, 0.0f, //
        0.5f,  0.5f,  0.0f, //
        -0.5f, 0.5f,  0.0f  //
    };

    Eva::Ref<Eva::VertexBuffer> squareVB;
    squareVB.reset(
        Eva::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
    squareVB->SetLayout({{Eva::ShaderDataType::Float3, "a_Position"}});
    m_SquareVA->AddVertexBuffer(squareVB);

    uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
    Eva::Ref<Eva::IndexBuffer> squareIB;
    squareIB.reset(Eva::IndexBuffer::Create(
        squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
    m_SquareVA->SetIndexBuffer(squareIB);

    m_FlatColorShader = Eva::Shader::Create("shaders/FlatColor.glsl");

    std::cout << "test1" << std::endl;
}

void SandBox2D::OnDetach() {}

void SandBox2D::OnUpdate(Eva::Timestep ts) {

    m_CameraController.OnUpdate(ts);

    Eva::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.00f});
    Eva::RenderCommand::Clear();

    Eva::Renderer::BeginScene(m_CameraController.GetCamera());

    std::dynamic_pointer_cast<Eva::OpenGLShader>(m_FlatColorShader)->Bind();
    std::dynamic_pointer_cast<Eva::OpenGLShader>(m_FlatColorShader)
        ->UploadUniformFloat4("u_Color", m_SquareColor);

    Eva::Renderer::Submit(m_FlatColorShader, m_SquareVA,
                          glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

    Eva::Renderer::EndScene();
}

void SandBox2D::OnImGuiRender() {
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}

void SandBox2D::OnEvent(Eva::Event &e) { m_CameraController.OnEvent(e); }
