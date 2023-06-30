/**
 * @file    :   Renderer.cpp
 * @date    :   2023/06/30 11:01:48
 * @author  :   yaojie
 * @version :   1.0
 */

#include "Renderer.h"

namespace Eva {

    void Renderer::BeginScene() {

    }

    void Renderer::EndScene() {

    }

    void Renderer::Submit(const std::shared_ptr<VertexArray> &vertexArray) {
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
} // namespace Eva
