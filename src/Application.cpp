/**
 * @file    :   Application.cpp
 * @date    :   2023/06/27 14:55:38
 * @author  :   yaojie
 * @version :   1.0
 */

#include "Application.h"
#include "SandBoxApp.h"
#include "ApplicationEvent.h"
#include "Log.h"

// class SandBox;

namespace Eva {

    Application::Application() {}

    Application::~Application() {}

    void Application::Run() {
        WindowResizeEvent e(1280, 720);
        if (e.IsInCategory(EventCategoryApplication)) {
            EVA_TRACE(e.ToString());
        }
        if (e.IsInCategory(EventCategoryInput)) {
            EVA_TRACE(e.ToString());
        }
        while (true)
            ;
    }
    Eva::Application *CreateApplication() { return new SandBox(); }
} // namespace Eva