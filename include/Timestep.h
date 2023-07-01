/**
 * @file    :   Timestep.h
 * @date    :   2023/07/01 13:51:46
 * @author  :   yaojie
 * @version :   1.0
 */

#pragma once

namespace Eva {

    class Timestep {
    public:
        Timestep(float time = 0.0f) : m_Time(time) {}

        operator float() const { return m_Time; }

        float GetSeconds() const { return m_Time; }
        float GetMilliSeconds() const { return m_Time * 1000.f; }

    private:
        float m_Time = 0.0f;
    };
} // namespace Eva
