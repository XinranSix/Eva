/**
 * @file    :   LayerStack.h
 * @date    :   2023/06/28 15:02:45
 * @author  :   Yao J
 * @version :   1.0
 */

#pragma once

#include <vector>

#include "Layer.h"

namespace Eva {

    class LayerStack {
    public:
        LayerStack();
        ~LayerStack();

        void PushLayer(Layer *layer);
        void PushOverlay(Layer *overlay);
        void PopLayer(Layer *layer);
        void PopOverlay(Layer *overlay);

        std::vector<Layer *>::iterator begin() { return m_Layers.begin(); }
        std::vector<Layer *>::iterator end() { return m_Layers.end(); }

    private:
        std::vector<Layer *> m_Layers;
        unsigned int m_LayerInsertIndex = 0;
    };
} // namespace Eva