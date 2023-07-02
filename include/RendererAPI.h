/**
 * @file    :   RendererAPI.h
 * @date    :   2023/06/30 18:56:27
 * @author  :   Yao J
 * @version :   1.0
 */

#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "VertexArray.h"
#include "eva/Core.h"

namespace Eva {

    class RendererAPI {
    public:
        enum class API { None = 0, OpenGL = 1 };

    public:
        virtual void Init() = 0;
        virtual void SetClearColor(const glm::vec4 &color) = 0;
        virtual void Clear() = 0;

        virtual void DrawIndexed(const Ref<VertexArray> &vertexArray) = 0;

        inline static API GetAPI() { return s_API; }

    private:
        static API s_API;
    };
} // namespace Eva
