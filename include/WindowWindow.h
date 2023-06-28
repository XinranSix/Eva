/**
 * @file    :   WindowWindow.h
 * @date    :   2023/06/28 11:59:03
 * @author  :   yaojie
 * @version :   1.0
 */

#pragma once

#include <GLFW/glfw3.h>
#include "Window.h"

namespace Eva {

    class WindowWindow : public Window {
    public:
        WindowWindow(const WindowProps &props);
        virtual ~WindowWindow();

        void OnUpdate() override;

        inline unsigned int GetWidth() const override { return m_Data.Width; }
        inline unsigned int GetHeight() const override { return m_Data.Height; }

        inline void SetEventCallback(const EventCallbackFn &callback) override {
            m_Data.EventCallback = callback;
        }
        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

    private:
        virtual void Init(const WindowProps &props);
        virtual void Shutdown();

    public:
        GLFWwindow *m_Window;

    private:
        struct WindowData {
            std::string Title;
            unsigned int Width, Height;

            bool VSync;

            EventCallbackFn EventCallback;
        };

        WindowData m_Data;
    };

} // namespace Eva
