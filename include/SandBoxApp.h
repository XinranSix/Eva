/**
 * @file    :   SandBoxApp.h
 * @date    :   2023/06/27 14:48:18
 * @author  :   yaojie
 * @version :   1.0
 */

#pragma once

#include "./Application.h"
#include "Layer.h"
#include "Log.h"
#include "LayerStack.h"
#include "Input.h"
#include "KeyCodes.h"
#include "Event.h"
#include "ApplicationEvent.h"
#include "KeyEvent.h"
#include "imgui.h"

// FIXME:示例 Layer
class ExampleLayer : public Eva::Layer {
public:
    ExampleLayer() : Layer("Example") {}

    void OnUpdate() override {
        // EVA_INFO("ExampleLayer::Update");
        if (Eva::Input::IsKeyPressed(EVA_KEY_TAB)) {
            EVA_TRACE("Tab key is pressed (poll)!");
        }
    }

    void OnImGuiRender() override {
        // ImGui::Begin("Test");
        // ImGui::Text("Hello World");
        // ImGui::End();
    }

    void OnEvent(Eva::Event &event) override {
        if (event.GetEventType() == Eva::EventType::KeyPressed) {
            Eva::KeyPressedEvent &e = (Eva::KeyPressedEvent &)event;
            if (e.GetKeyCode() == EVA_KEY_TAB) {
                EVA_TRACE("Tab key is pressed (event)!");
            }
            EVA_TRACE("{0}", (char)e.GetKeyCode());
        }
    }
};

class SandBox : public Eva::Application {
public:
    SandBox();

    ~SandBox();
};
