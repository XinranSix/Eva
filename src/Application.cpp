/**
 * @file    :   Application.cpp
 * @date    :   2023/06/27 14:55:38
 * @author  :   yaojie
 * @version :   1.0
 */

#include "Application.h"
#include "SandBoxApp.h"
// #include "ApplicationEvent.h"
#include "Log.h"
#include <memory>

// #include <glad/glad.h>

#include <GLFW/glfw3.h>

// class SandBox;

namespace Eva {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

    Application::Application() {
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
    }

    Application::~Application() {}

    void Application::OnEvent(Event &e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(
            BIND_EVENT_FN(Application::OnWindownClose));
        EVA_CORE_TRACE("{0}", e.ToString());
    }

    void Application::Run() {

        while (m_Running) {
            // glClearColor(1, 0, 1, 1);
            // glClear(GL_COLOR_BUFFER_BIT);
            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindownClose(WindowCloseEvent &e) {
        m_Running = false;
        return true;
    }

    Eva::Application *CreateApplication() { return new SandBox(); }
} // namespace Eva