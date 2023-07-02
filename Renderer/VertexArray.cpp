/**
 * @file    :   VertexArray.cpp
 * @date    :   2023/06/30 14:55:40
 * @author  :   Yao J
 * @version :   1.0
 */

#include "Renderer.h"
#include "VertexArray.h"
#include "OpenGLVertexArray.h"
#include <memory>

namespace Eva {

    Ref<VertexArray> VertexArray::Create() {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::None:
            EVA_CORE_ASSERT(false,
                            "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLVertexArray>();
        }
        EVA_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }
} // namespace Eva
