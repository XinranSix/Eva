/**
 * @file    :   Appliction.h
 * @date    :   2023/06/27 13:59:29
 * @author  :   yaojie
 * @version :   1.0
 */

#pragma once

#include "Window.h"
#include "eva/eva.h"
#include <memory>
#include "ApplicationEvent.h"
#include "Layer.h"
#include "LayerStack.h"

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
        bool OnWindownClose(WindowCloseEvent &e);

        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
        LayerStack m_LayerStack;

    private:
        static Application *s_Instance;
    };

    Application *CreateApplication();

} // namespace Eva