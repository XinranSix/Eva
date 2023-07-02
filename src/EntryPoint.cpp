/**
 * @file    :   EntryPoint.h
 * @date    :   2023/06/27 14:18:24
 * @author  :   Yao J
 * @version :   1.0
 * Engin Entry Point
 */

#include "Log.h"
#include "Application.h"

// extern GameEngine::Application *GameEngine::CreateApplication();

int main(int argc, char *argv[]) {
    Eva::Log::Init();

    EVA_CORE_WARN("Initialized Log!");
    int a = 5;
    EVA_INFO("Hello! Var={0}", a);

    auto app = Eva::CreateApplication();
    app->Run();
    delete app;

    return 0;
}
