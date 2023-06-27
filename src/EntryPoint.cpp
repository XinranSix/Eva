/**
 * @file    :   EntryPoint.h
 * @date    :   2023/06/27 14:18:24
 * @author  :   yaojie
 * @version :   1.0
 */

#pragma once

#include "Application.h"
#include "Log.h"

// extern GameEngine::Application *GameEngine::CreateApplication();

int main(int argc, char *argv[]) {
    Eva::Log::Init();
    GE_CORE_WARN("Initialized Log!");
    int a = 5;
    GE_INFO("Hello! Var={0}", a);

    auto app = Eva::CreateApplication();
    app->Run();
    delete app;
    return 0;
}
