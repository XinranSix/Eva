/**
 * @file    :   VertexArray.cpp
 * @date    :   2023/06/30 14:55:40
 * @author  :   yaojie
 * @version :   1.0
 */

#include "VertexArray.h"
#include "Renderer.h"
#include "OpenGLVertexArray.h"

namespace Eva {

    VertexArray *VertexArray::Create() {
        switch (Renderer::GetAPI()) {
        case RendererAPI::None:
            EVA_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::OpenGL:
            return new OpenGLVertexArray();
        }
        EVA_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }
} // namespace Eva
