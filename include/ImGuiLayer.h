/**
 * @file    :   ImGuiLayer.h
 * @date    :   2023/06/28 19:15:54
 * @author  :   Yao J
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

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnImGuiRender() override;

        void Begin();
        void End();

    private:
        float m_Time = 0.0f;
    };
} // namespace Eva
