/**
 * @file    :   Renderer.cpp
 * @date    :   2023/06/30 11:01:48
 * @author  :   Yao J
 * @version :   1.0
 */

#include "Renderer.h"
#include "OpenGLShader.h"
#include "eva/Core.h"

#include <memory>

namespace Eva {

    Renderer::SceneData *Renderer::m_SceneData = new Renderer::SceneData;

    void Renderer::BeginScene(OrthographicCamera &camera) {
        m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene() {}

    void Renderer::Submit(const Ref<Shader> &shader,
                          const Ref<VertexArray> &vertexArray,
                          const glm::mat4 &transform) {

        shader->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4(
            "u_ViewProjection", m_SceneData->ViewProjectionMatrix);
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4(
            "u_Transform", transform);

        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
} // namespace Eva
