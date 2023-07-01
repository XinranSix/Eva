/**
 * @file    :   OpenGLRendererAPI.cpp
 * @date    :   2023/06/30 19:36:42
 * @author  :   Yao J
 * @version :   1.0
 */

#include <cstddef>
#include <glad./glad.h>

#include "OpenGLRendererAPI.h"
#include "eva/Core.h"

namespace Eva {

    void OpenGLRendererAPI::SetClearColor(const glm::vec4 &color) {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRendererAPI::Clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRendererAPI::DrawIndexed(
        const Ref<VertexArray> &vertexArray) {
        glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffers()->GetCount(),
                       GL_UNSIGNED_INT, nullptr);
    }
} // namespace Eva
