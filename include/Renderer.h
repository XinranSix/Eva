/**
 * @file    :   Renderer.h
 * @date    :   2023/06/30 10:59:39
 * @author  :   yaojie
 * @version :   1.0
 */

#pragma once

#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Shader.h"

namespace Eva {

    class Renderer {
    public:
        static void BeginScene(OrthographicCamera &camera);
        static void EndScene();
        static void Submit(const std::shared_ptr<Shader> &shader,
                           const std::shared_ptr<VertexArray> &vertexArray);

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
