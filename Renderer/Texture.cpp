/**
 * @file    :   Texture.cpp
 * @date    :   2023/07/01 22:00:40
 * @author  :   Yao J
 * @version :   1.0
 */

#include <memory>

#include "Texture.h"
#include "eva/Core.h"
#include "Renderer.h"
#include "OpenGLTexture.h"

namespace Eva {

    Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height) {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::None:
            EVA_CORE_ASSERT(false,
                            "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLTexture2D>(width, height);
        }
        EVA_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }

    Ref<Texture2D> Texture2D::Create(const std::string &path) {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::None:
            EVA_CORE_ASSERT(false,
                            "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLTexture2D>(path);
        }
        EVA_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }
} // namespace Eva
