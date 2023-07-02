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

#include "SandBox2D.h"
#include "Renderer2D.h"
#include "OpenGLShader.h"
#include "RenderCommand.h"

SandBox2D::SandBox2D()
    : Layer("SandBox2D"), m_CameraController(1280.0f / 720.f, true) {}

void SandBox2D::OnAttach() {
    m_CheckerboardTexture =
        Eva::Texture2D::Create("./assets/textures/Checkerboard.png");
}

void SandBox2D::OnDetach() {}

void SandBox2D::OnUpdate(Eva::Timestep ts) {

    m_CameraController.OnUpdate(ts);

    Eva::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.00f});
    Eva::RenderCommand::Clear();

    Eva::Renderer2D::BeginScene(m_CameraController.GetCamera());
    Eva::Renderer2D::DrawQuad({-1.0f, 0.0f}, {0.8f, 0.8f},
                              {0.8f, 0.2f, 0.3f, 1.0f});
    Eva::Renderer2D::DrawQuad({0.5f, -0.5f}, {0.5f, 0.75f},
                              {0.2f, 0.3f, 0.8f, 1.0f});
    Eva::Renderer2D::DrawQuad({0.0f, 0.0f,-0.1f}, {10.0f, 10.0f},
                              m_CheckerboardTexture);
    Eva::Renderer2D::EndScene();
}

void SandBox2D::OnImGuiRender() {
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}

void SandBox2D::OnEvent(Eva::Event &e) { m_CameraController.OnEvent(e); }
