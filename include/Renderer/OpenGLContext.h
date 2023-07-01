/**
 * @file    :   OpenGLContext.h
 * @date    :   2023/06/29 19:47:38
 * @author  :   Yao J
 * @version :   1.0
 */

#pragma once

#include <GLFW/glfw3.h>

#include "Renderer/GraphicsContext.h"

namespace Eva {
    class OpenGLContext : public GraphicsContext {
    public:
        OpenGLContext(GLFWwindow *windowHandle);

        virtual void Init() override;
        virtual void SwapBuffers() override;

    private:
        GLFWwindow *m_WindowHandle;
    };
} // namespace Eva
