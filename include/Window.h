/**
 * @file    :   Window.h
 * @date    :   2023/06/28 11:49:46
 * @author  :   Yao J
 * @version :   1.0
 */

#pragma once

#include <functional>

#include "Event.h"
#include "eva/Core.h"

namespace Eva {

    struct WindowProps {
        std::string Title;
        unsigned int Width;
        unsigned int Height;

        WindowProps(const std::string &title = "Eva Engine",
                    unsigned int width = 1280, unsigned int height = 720)
            : Title(title), Width(width), Height(height) {}
    };

    class Window {
    public:
        using EventCallbackFn = std::function<void(Event &)>;

        virtual ~Window() {}

        virtual void OnUpdate() = 0;

        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;

        virtual void SetEventCallback(const EventCallbackFn &callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;

        virtual void *GetNativeWindow() const = 0;

        static Window *Create(const WindowProps &props = WindowProps());
    };
} // namespace Eva
