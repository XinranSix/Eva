/**
 * @file    :   OrthographicCameraController.h
 * @date    :   2023/07/02 14:19:37
 * @author  :   Yao J
 * @version :   1.0
 */

#pragma once

#include "Event.h"
#include "Timestep.h"
#include "MouseEvent.h"
#include "ApplicationEvent.h"
#include "OrthographicCamera.h"

namespace Eva {

    class OrthographicCameraController {
    public:
        OrthographicCameraController(float aspectRatio);

        void OnUpdate(Timestep ts);
        void OnEvent(Event &t);

    private:
        bool OnMouseScrolled(MouseScrolledEvent &e);
        bool OnWindowResized(WindowResizeEvent &e);

    private:
        float m_AspectRatio;
        float z_ZoomLevel = 1.0f;
        OrthographicCamera m_Camera;
    };
} // namespace Eva
