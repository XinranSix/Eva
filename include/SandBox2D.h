/**
 * @file    :   SandBox2D.h
 * @date    :   2023/07/02 19:07:04
 * @author  :   Yao J
 * @version :   1.0
 */

#pragma once

#include "Layer.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "OrthographicCameraController.h"

class SandBox2D : public Eva::Layer {
public:
    SandBox2D();
    virtual ~SandBox2D() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    void OnUpdate(Eva::Timestep ts) override;
    virtual void OnImGuiRender() override;
    void OnEvent(Eva::Event &e) override;

private:
    Eva::OrthographicCameraController m_CameraController;

    Eva::Ref<Eva::VertexArray> m_SquareVA;
    Eva::Ref<Eva::Shader> m_FlatColorShader;

    Eva::Ref<Eva::Texture2D> m_CheckerboardTexture;

    glm::vec4 m_SquareColor = {0.2f, 0.3f, 0.8f, 1.0f};
};
