/**
 * @file    :   OpenGLRendererAPI.h
 * @date    :   2023/06/30 19:36:07
 * @author  :   Yao J
 * @version :   1.0
 */

#pragma once

#include "eva/Core.h"
#include "RendererAPI.h"

namespace Eva {

    class OpenGLRendererAPI : public RendererAPI {
    public:
        virtual void Init() override;
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width,
                                 uint32_t height) override;
        virtual void SetClearColor(const glm::vec4 &color) override;
        virtual void Clear() override;

        virtual void DrawIndexed(const Ref<VertexArray> &vertexArray) override;
    };
} // namespace Eva
