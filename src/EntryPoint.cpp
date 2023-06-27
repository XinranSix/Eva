/**
 * @file    :   EntryPoint.h
 * @date    :   2023/06/27 14:18:24
 * @author  :   yaojie
 * @version :   1.0
 */

#pragma once

#include "Application.h"
#include <cstdio>

extern GameEngine::Application *GameEngine::CreateApplication();

int main(int argc, char *argv[]) {
    printf("Game Engigen\n");
    auto app = GameEngine::CreateApplication();
    app->Run();
    delete app;
    return 0;
}
