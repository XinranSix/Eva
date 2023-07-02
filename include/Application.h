/**
 * @file    :   Appliction.h
 * @date    :   2023/06/27 13:59:29
 * @author  :   Yao J
 * @version :   1.0
 */

#pragma once

#include <memory>

#include "Layer.h"
#include "Shader.h"
#include "Buffer.h"
#include "Window.h"
#include "eva/eva.h"
#include "Timestep.h"
#include "LayerStack.h"
#include "ImGuiLayer.h"
#include "VertexArray.h"
#include "ApplicationEvent.h"
#include "OrthographicCamera.h"

namespace Eva {
    class Application {
    public:
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event &e);

        void PushLayer(Layer *layer);
        void PushOverlay(Layer *layer);

        inline Window &GetWindow() { return *m_Window; }

        static inline Application &Get() { return *s_Instance; }

    private:
        bool OnWindowClose(WindowCloseEvent &e);
        bool OnWindowResize(WindowResizeEvent &e);

    private:
        std::unique_ptr<Window> m_Window;
        ImGuiLayer *m_ImGuiLayer;
        bool m_Running = true;
        bool m_Minimized = false;
        LayerStack m_LayerStack;
        Timestep m_Timestep;
        float m_LastFrameTime = 0.0f;

    private:
        static Application *s_Instance;
    };

    Application *CreateApplication();

} // namespace Eva
