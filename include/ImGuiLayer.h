/**
 * @file    :   ImGuiLayer.h
 * @date    :   2023/06/28 19:15:54
 * @author  :   yaojie
 * @version :   1.0
 */

#pragma once

#include "Layer.h"
#include "KeyEvent.h"
#include "MouseEvent.h"
#include "ApplicationEvent.h"

namespace Eva {

    class ImGuiLayer : public Layer {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach();
        void OnDetach();
        void OnUpdate();
        void OnEvent(Event &event);

    private:
        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent &e);
        bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent &e);
        bool OnMouseMovedEvent(MouseMovedEvent &e);
        bool OnMouseScrolledEvent(MouseScrolledEvent &e);
        bool OnKeyPressedEvent(KeyPressedEvent &e);
        bool OnKeyReleasedEvent(KeyReleasedEvent &e);
        bool OnKeyTypedEvent(KeyTypedEvent &e);
        bool OnWindowResizedEvent(WindowResizeEvent &e);

    private:
        float m_Time = 0.0f;
    };
} // namespace Eva
