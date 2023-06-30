/**
 * @file    :   Renderer.h
 * @date    :   2023/06/30 10:59:39
 * @author  :   yaojie
 * @version :   1.0
 */

#pragma once

#include "RenderCommand.h"

namespace Eva {

    class Renderer {
    public:
        static void BeginScene();
        static void EndScene();
        static void Submit(const std::shared_ptr<VertexArray> &vertexArray);

        inline static RendererAPI::API GetAPI() {
            return RendererAPI::GetAPI();
        }
    };
} // namespace Eva
