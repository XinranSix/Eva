/**
 * @file    :   Shader.cpp
 * @date    :   2023/06/29 22:13:33
 * @author  :   Yao J
 * @version :   1.0
 */

#include <memory>
#include <vector>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Renderer.h"
#include "OpenGLShader.h"
#include "eva/Assert.h"

namespace Eva {

    Ref<Shader> Shader::Create(const std::string &filepath) {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::None:
            EVA_CORE_ASSERT(false,
                            "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLShader>(filepath);
        }
        EVA_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }

    Ref<Shader> Shader::Create(const std::string &name,
                               const std::string &vertexSrc,
                               const std::string &fragmentSrc) {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::None:
            EVA_CORE_ASSERT(false,
                            "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
        }
        EVA_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }

    /* --------------------------------------------------------------------------
     */

    void ShaderLibrary::Add(const std::string &name,
                            const Ref<Shader> &shader) {
        EVA_CORE_ASSERT(!Exists(name), "Shader already exists!");
        m_Shaders[name] = shader;
    }

    void ShaderLibrary::Add(const Ref<Shader> &shader) {
        auto &name = shader->GetName();
        Add(name, shader);
    }

    Ref<Shader> ShaderLibrary::Load(const std::string &filepath) {
        auto shader = Shader::Create(filepath);
        Add(shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::Load(const std::string &name,
                                    const std::string &filepath) {
        auto shader = Shader::Create(filepath);
        Add(name, shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::Get(const std::string &name) {
        EVA_CORE_ASSERT(Exists(name), "Shader not found!");
        return m_Shaders[name];
    }

    bool ShaderLibrary::Exists(const std::string &name) const {
        return m_Shaders.find(name) != m_Shaders.end();
    }

} // namespace Eva
