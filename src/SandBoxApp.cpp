/**
 * @file    :   SandBoxApp.cpp
 * @date    :   2023/06/27 15:06:27
 * @author  :   yaojie
 * @version :   1.0
 */

#include "Application.h"
#include "SandBoxApp.h"

SandBox::SandBox() {

    PushLayer(new ExampleLayer());

    // PushOverlay(new Eva::ImGuiLayer());
}

SandBox::~SandBox() {}
