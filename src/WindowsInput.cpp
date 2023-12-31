/**
 * @file    :   WindowsInput.cpp
 * @date    :   2023/06/29 10:42:50
 * @author  :   Yao J
 * @version :   1.0
 */

#include <GLFW/glfw3.h>

#include "WindowsInput.h"
#include "Application.h"

namespace Eva {

    Input *Input::s_Instance = new WindowsInput();

    bool WindowsInput::IsKeyPressedImpl(int keycode) {

        auto window = static_cast<GLFWwindow *>(
            Application::Get().GetWindow().GetNativeWindow());

        auto state = glfwGetKey(window, keycode);

        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool WindowsInput::IsMouseButtonPressedImpl(int button) {
        auto window = static_cast<GLFWwindow *>(
            Application::Get().GetWindow().GetNativeWindow());

        auto state = glfwGetMouseButton(window, button);

        return state == GLFW_PRESS;
    }

    std::pair<float, float> WindowsInput::GetMousePositionImpl() {
        auto window = static_cast<GLFWwindow *>(
            Application::Get().GetWindow().GetNativeWindow());
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        return {(float)xpos, (float)ypos};
    }

    float WindowsInput::GetMouseXImpl() {
        auto [x, y] = GetMousePositionImpl();
        return x;
    }

    float WindowsInput::GetMouseYImpl() {
        auto [x, y] = GetMousePositionImpl();
        return y;
    }
} // namespace Eva
