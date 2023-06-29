/**
 * @file    :   WindowsInput.h
 * @date    :   2023/06/29 10:42:42
 * @author  :   yaojie
 * @version :   1.0
 */

#pragma once

#include "Input.h"

namespace Eva {

    class WindowsInput : public Input {
    protected:
        virtual bool IsKeyPressedImpl(int keycode) override;

        virtual bool IsMouseButtonPressedImpl(int button) override;
        virtual std::pair<float, float> GetMousePositionImpl() override;
        virtual float GetMouseXImpl() override;
        virtual float GetMouseYImpl() override;
    };
} // namespace Eva
