/**
 * @file    :   OpenGLContext.cpp
 * @date    :   2023/06/29 19:49:40
 * @author  :   yaojie
 * @version :   1.0
 */

// #include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Renderer/OpenGLContext.h"
#include "eva/Assert.h"

namespace Eva {

    OpenGLContext::OpenGLContext(GLFWwindow *windowHandle)
        : m_WindowHandle(windowHandle) {
        EVA_CORE_ASSERT(windowHandle, "Window handle is null!");
    }

    void OpenGLContext::Init() {
        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        EVA_CORE_ASSERT(status, "Failed to initailize Glad!");
    }

    void OpenGLContext::SwapBuffers() { glfwSwapBuffers(m_WindowHandle); }

} // namespace Eva
