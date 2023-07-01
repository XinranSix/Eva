/**
 * @file    :   GraphicsContext.h
 * @date    :   2023/06/29 19:45:36
 * @author  :   Yao J
 * @version :   1.0
 */

#pragma once

namespace Eva {

    class GraphicsContext {
    public:
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;
    };
} // namespace Eva
