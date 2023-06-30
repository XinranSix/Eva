/**
 * @file    :   Renderer.h
 * @date    :   2023/06/30 10:59:39
 * @author  :   yaojie
 * @version :   1.0
 */

#pragma once

namespace Eva {

    enum class RendererAPI { None = 0, OpenGL = 1 };

    class Renderer {
    public:
        inline static RendererAPI GetAPI() { return s_RendererAPI; }

        static RendererAPI s_RendererAPI;
    };
} // namespace Eva
