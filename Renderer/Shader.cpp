/**
 * @file    :   Shader.cpp
 * @date    :   2023/06/29 22:13:33
 * @author  :   Yao J
 * @version :   1.0
 */

#include <glad/glad.h>
#include <vector>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Renderer.h"
#include "OpenGLShader.h"
#include "eva/Assert.h"

namespace Eva {

    Shader *Shader::Create(const std::string &filepath) {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::None:
            EVA_CORE_ASSERT(false,
                            "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return new OpenGLShader(filepath);
        }
    }

    Shader *Shader::Create(const std::string &vertexSrc,
                           const std::string &fragmentSrc) {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::None:
            EVA_CORE_ASSERT(false,
                            "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return new OpenGLShader(vertexSrc, fragmentSrc);
        }
        EVA_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }

} // namespace Eva
