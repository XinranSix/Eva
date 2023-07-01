/**
 * @file    :   RenderCommand.h
 * @date    :   2023/06/30 19:07:14
 * @author  :   yaojie
 * @version :   1.0
 */

#pragma once

#include "RendererAPI.h"

namespace Eva {

    class RenderCommand {
    public:
        inline static void SetClearColor(const glm::vec4 &color) {
            s_RendererAPI->SetClearColor(color);
        }

        inline static void Clear() { s_RendererAPI->Clear(); }

        inline static void
        DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray) {
            s_RendererAPI->DrawIndexed(vertexArray);
        }

    private:
        static RendererAPI *s_RendererAPI;
    };
} // namespace Eva