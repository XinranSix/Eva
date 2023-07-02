/**
 * @file    :   SandBoxApp.cpp
 * @date    :   2023/06/27 15:06:27
 * @author  :   Yao J
 * @version :   1.0
 */

#include "SandBox2D.h"
#include "SandBoxApp.h"
#include "Application.h"

SandBox::SandBox() {
    // PushLayer(new ExampleLayer());
    PushOverlay(new SandBox2D());
}

SandBox::~SandBox() {}
