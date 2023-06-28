/**
 * @file    :   ImGui.h
 * @date    :   2023/06/28 19:15:54
 * @author  :   yaojie
 * @version :   1.0
 */

#pragma once

#include "Layer.h"

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
        float m_Time = 0.0f;
    };
} // namespace Eva
