/**
 * @file    :   OrthographicCameraController.cpp
 * @date    :   2023/07/02 14:20:25
 * @author  :   Yao J
 * @version :   1.0
 */

#include "Input.h"
#include "KeyCodes.h"
#include "OrthographicCameraController.h"

namespace Eva {

    OrthographicCameraController::OrthographicCameraController(
        float aspectRatio, bool rotation)
        : m_AspectRatio(aspectRatio),
          m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel,
                   -m_ZoomLevel, m_ZoomLevel),
          m_Rotation(rotation) {}

    void OrthographicCameraController::OnUpdate(Timestep ts) {
        if (Input::IsKeyPressed(EVA_KEY_A)) {
            m_CameraPosition.x -= m_CameraTramslationSpeed * ts;
        } else if (Input::IsKeyPressed(EVA_KEY_D)) {
            m_CameraPosition.x += m_CameraTramslationSpeed * ts;
        }

        if (Input::IsKeyPressed(EVA_KEY_W)) {
            m_CameraPosition.y += m_CameraTramslationSpeed * ts;
        } else if (Input::IsKeyPressed(EVA_KEY_S)) {
            m_CameraPosition.y -= m_CameraTramslationSpeed * ts;
        }

        if (m_Rotation) {
            if (Input::IsKeyPressed(EVA_KEY_Q)) {
                m_CameraRotation += m_CameraRotationSpeed * ts;
            } else if (Input::IsKeyPressed(EVA_KEY_E)) {
                m_CameraRotation -= m_CameraRotationSpeed * ts;
            }
            m_Camera.SetRotation(m_CameraRotation);
        }
        m_Camera.SetPosition(m_CameraPosition);

        m_CameraTramslationSpeed = m_ZoomLevel;
    }

    void OrthographicCameraController::OnEvent(Event &e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(
            EVA_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizeEvent>(
            EVA_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
    }

    bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent &e) {
        m_ZoomLevel -= e.GetYOffset() * 0.5f;
        m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel,
                               m_AspectRatio * m_ZoomLevel, -m_ZoomLevel,
                               m_ZoomLevel);
        return false;
    }

    bool OrthographicCameraController::OnWindowResized(WindowResizeEvent &e) {
        m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel,
                               m_AspectRatio * m_ZoomLevel, -m_ZoomLevel,
                               m_ZoomLevel);
        return false;
    }
}; // namespace Eva
