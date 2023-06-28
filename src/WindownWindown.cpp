/**
 * @file    :   WindowWindow.cpp
 * @date    :   2023/06/28 12:06:55
 * @author  :   yaojie
 * @version :   1.0
 */

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "WindowWindow.h"
#include "Log.h"
#include "eva/Assert.h"
#include "KeyEvent.h"
#include "MouseEvent.h"
#include "ApplicationEvent.h"

namespace Eva {

    static bool s_GLFWInitialized = false;

    static void GLFWSetErrorCallback(int error, const char *description) {
        EVA_CORE_ERROE("GLFW Error ({0}) : {1}", error, description);
    }

    Window *Window::Create(const WindowProps &props) {
        return new WindowWindow(props);
    }

    WindowWindow::WindowWindow(const WindowProps &props) { Init(props); }

    WindowWindow::~WindowWindow() { Shutdown(); }

    void WindowWindow::Init(const WindowProps &props) {
        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;

        EVA_CORE_INFO("Creating window {0} ({1}, {2})", props.Title,
                      props.Width, props.Height);

        if (!s_GLFWInitialized) {
            int success = glfwInit();
            EVA_CORE_ASSERT(success, "Could not initalize GLFW!");
            glfwSetErrorCallback(GLFWSetErrorCallback);
            s_GLFWInitialized = true;
        }
        m_Window = glfwCreateWindow((int)props.Width, (int)props.Height,
                                    m_Data.Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        EVA_CORE_ASSERT(status, "Failed to initailize Glad!");
        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);

        // Set GLFW callbacks
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow *window, int width,
                                               int height) {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
            data.Width = width;
            data.Height = height;

            WindowResizeEvent event(width, height);
            data.EventCallback(event);
        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *window) {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.EventCallback(event);
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow *window, int key,
                                        int scancode, int action, int mods) {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
            switch (action) {
            case GLFW_PRESS: {
                KeyPressedEvent event(key, 0);
                data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE: {
                KeyReleasedEvent event(key);
                data.EventCallback(event);
                break;
            }
            case GLFW_REPEAT: {
                KeyPressedEvent event(key, 1);
                data.EventCallback(event);
                break;
            }
            }
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow *window, int button,
                                                int action, int mods) {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

            switch (action) {
            case GLFW_PRESS: {
                MouseButtonPressedEvent event(button);
                data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE: {
                MouseButtonReleasedEvent event(button);
                data.EventCallback(event);
                break;
            }
            }
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow *window, double xOffset,
                                           double yOffset) {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            data.EventCallback(event);
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow *window, double xPos,
                                              double yPos) {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
            MouseMovedEvent event((float)xPos, (float)yPos);
            data.EventCallback(event);
        });
    }

    void WindowWindow::Shutdown() { glfwDestroyWindow(m_Window); }

    void WindowWindow::OnUpdate() {

        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    void WindowWindow::SetVSync(bool enabled) {
        if (enabled) {
            glfwSwapInterval(1);
        } else {
            glfwSwapInterval(0);
        }
        m_Data.VSync = enabled;
    }

    bool WindowWindow::IsVSync() const { return m_Data.VSync; }

} // namespace Eva
