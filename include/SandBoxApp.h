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

// FIXME:示例 Layer
class ExampleLayer : public Eva::Layer {
public:
    ExampleLayer() : Layer("Example") {}

    void OnUpdate() override { EVA_INFO("ExampleLayer::Update"); }

    void OnEvent(Eva::Event &event) override {
        EVA_CORE_TRACE("{0}", event.ToString());
    }
};

class SandBox : public Eva::Application {
public:
    SandBox();

    ~SandBox();
};
