/**
 * @file    :   OpenGLContext.cpp
 * @date    :   2023/06/29 19:49:40
 * @author  :   Yao J
 * @version :   1.0
 */

// #include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Log.h"
#include "eva/Assert.h"
#include "Renderer/OpenGLContext.h"

namespace Eva {

    OpenGLContext::OpenGLContext(GLFWwindow *windowHandle)
        : m_WindowHandle(windowHandle) {
        EVA_CORE_ASSERT(windowHandle, "Window handle is null!");
    }

    void OpenGLContext::Init() {
        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        EVA_CORE_ASSERT(status, "Failed to initailize Glad!");

        EVA_CORE_INFO("OpenGL Info:");
        EVA_CORE_INFO("  Vendor: {0}", (const char *)glGetString(GL_VENDOR));
        EVA_CORE_INFO("  Renderer: {0}",
                      (const char *)glGetString(GL_RENDERER));
        EVA_CORE_INFO("  Version: {0}", (const char *)glGetString(GL_VERSION));
    }

    void OpenGLContext::SwapBuffers() { glfwSwapBuffers(m_WindowHandle); }

} // namespace Eva
