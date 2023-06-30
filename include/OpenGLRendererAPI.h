/**
 * @file    :   OpenGLRendererAPI.h
 * @date    :   2023/06/30 19:36:07
 * @author  :   yaojie
 * @version :   1.0
 */

#pragma once

#include "RendererAPI.h"

namespace Eva {

    class OpenGLRendererAPI : public RendererAPI {
    public:
        virtual void SetClearColor(const glm::vec4 &color) override;
        virtual void Clear() override;

        virtual void
        DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray) override;
    };
} // namespace Eva
