/**
 * @file    :   SandBoxApp.cpp
 * @date    :   2023/06/27 15:06:27
 * @author  :   Yao J
 * @version :   1.0
 */

#include "SandBoxApp.h"
#include "Application.h"

SandBox::SandBox() {

    PushLayer(new ExampleLayer());

    // PushOverlay(new Eva::ImGuiLayer());
}

SandBox::~SandBox() {}
