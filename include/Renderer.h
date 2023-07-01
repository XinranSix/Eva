/**
 * @file    :   Renderer.h
 * @date    :   2023/06/30 10:59:39
 * @author  :   Yao J
 * @version :   1.0
 */

#pragma once

#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Shader.h"
#include "eva/Core.h"

namespace Eva {

    class Renderer {
    public:
        static void BeginScene(OrthographicCamera &camera);
        static void EndScene();
        static void Submit(const Ref<Shader> &shader,
                           const Ref<VertexArray> &vertexArray,
                           const glm::mat4 &transform = glm::mat4(1.0f));

        inline static RendererAPI::API GetAPI() {
            return RendererAPI::GetAPI();
        }

    private:
        struct SceneData {
            glm::mat4 ViewProjectionMatrix;
        };

        static SceneData *m_SceneData;
    };
} // namespace Eva
