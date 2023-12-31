/**
 * @file    :   Layer.h
 * @date    :   2023/06/28 15:02:25
 * @author  :   Yao J
 * @version :   1.0
 */

#pragma once

#include "Event.h"
#include "eva/eva.h"
#include "Timestep.h"

namespace Eva {

    class Layer {
    public:
        Layer(const std::string &name = "Layer");
        virtual ~Layer();

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(Timestep ts) {}
        virtual void OnImGuiRender() {}
        virtual void OnEvent(Event &event) {}

        inline const std::string &GetName() const { return m_DebugName; }

    protected:
        std::string m_DebugName;
    };
} // namespace Eva