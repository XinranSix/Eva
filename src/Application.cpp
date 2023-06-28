/**
 * @file    :   Application.cpp
 * @date    :   2023/06/27 14:55:38
 * @author  :   yaojie
 * @version :   1.0
 */

#include "Application.h"
#include "SandBoxApp.h"
// #include "ApplicationEvent.h"
// #include "Log.h"
#include "eva/Assert.h"

#include <memory>

#include <glad/glad.h>

// #include <GLFW/glfw3.h>

// class SandBox;

namespace Eva {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

    // static Application *Application::s_Instance = nullptr;
    Application *Application::s_Instance = nullptr;

    Application::Application() {
        EVA_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
    }

    Application::~Application() {}

    void Application::OnEvent(Event &e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(
            BIND_EVENT_FN(Application::OnWindownClose));

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
            (*--it)->OnEvent(e);
            if (e.Handled) {
                break;
            }
        }
    }

    void Application::PushLayer(Layer *layer) {
        // HZ_PROFILE_FUNCTION();
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer *layer) {
        // HZ_PROFILE_FUNCTION();
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::Run() {
        while (m_Running) {
            glClearColor(0.77, 0.44, 0.55, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            for (Layer *layer : m_LayerStack) {
                layer->OnUpdate();
            }
            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindownClose(WindowCloseEvent &e) {
        m_Running = false;
        return true;
    }

    Eva::Application *CreateApplication() { return new SandBox(); }
} // namespace Eva