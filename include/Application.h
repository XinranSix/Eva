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

namespace Eva {
    class Application {
    public:
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event &e);

    private:
        bool OnWindownClose(WindowCloseEvent &e);

        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
    };

    Application *CreateApplication();

} // namespace Eva