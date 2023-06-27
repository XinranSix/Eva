/**
 * @file    :   Appliction.h
 * @date    :   2023/06/27 13:59:29
 * @author  :   yaojie
 * @version :   1.0
 */

#pragma once

namespace Eva {
    class Application {
    public:
        Application();
        virtual ~Application();

        void Run();
    };

    Application *CreateApplication();

} // namespace GameEngine