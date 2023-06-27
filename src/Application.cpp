/**
 * @file    :   Application.cpp
 * @date    :   2023/06/27 14:55:38
 * @author  :   yaojie
 * @version :   1.0
 */

#include "Application.h"
#include "SandBoxApp.h"

class SandBox;

namespace Eva {

    Application::Application() {}

    Application::~Application() {}

    void Application::Run() {
        while (true)
            ;
    }
    Eva::Application *CreateApplication() { return new SandBox(); }
} // namespace GameEngine