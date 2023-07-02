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
        OrthographicCameraController(float aspectRatio, bool rotation = false);

        void OnUpdate(Timestep ts);
        void OnEvent(Event &e);

        OrthographicCamera &GetCamera() { return m_Camera; }
        const OrthographicCamera &GetCamera() const { return m_Camera; }

    private:
        bool OnMouseScrolled(MouseScrolledEvent &e);
        bool OnWindowResized(WindowResizeEvent &e);

    private:
        float m_AspectRatio;
        float m_ZoomLevel = 1.0f;
        OrthographicCamera m_Camera;

        bool m_Rotation;
        glm::vec3 m_CameraPosition = {0.0f, 0.0f, 0.0f};
        float m_CameraRotation = 0.0f;

        float m_CameraTramslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
    };
} // namespace Eva
