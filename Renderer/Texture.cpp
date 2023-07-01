/**
 * @file    :   Texture.cpp
 * @date    :   2023/07/01 22:00:40
 * @author  :   Yao J
 * @version :   1.0
 */

#include <memory>

#include "Texture.h"
#include "Renderer.h"
#include "OpenGLTexture.h"

namespace Eva {

    Ref<Texture2D> Texture2D::Create(const std::string &path) {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::None:
            EVA_CORE_ASSERT(false,
                            "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return  std::make_shared<OpenGLTexture2D>(path);
        }
        EVA_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }
} // namespace Eva
