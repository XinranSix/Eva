/**
 * @file    :   OrthographicCameraController.cpp
 * @date    :   2023/07/02 14:20:25
 * @author  :   Yao J
 * @version :   1.0
 */

#include "OrthographicCameraController.h"

namespace Eva {

    OrthographicCameraController::OrthographicCameraController(
        float aspectRatio) {}

    void OrthographicCameraController::OnUpdate(Timestep ts) {}

    void OrthographicCameraController::OnEvent(Event &t) {}

    bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent &e) {}

    bool OrthographicCameraController::OnWindowResized(WindowResizeEvent &e) {}
}; // namespace Eva
