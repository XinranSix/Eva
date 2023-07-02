/**
 * @file    :   Renderer2D.h
 * @date    :   2023/07/02 20:27:20
 * @author  :   Yao J
 * @version :   1.0
 */

#pragma once

#include "Texture.h"
#include "OrthographicCamera.h"

namespace Eva {

    class Renderer2D {
    public:
        static void Init();
        static void Shutdown();

        static void BeginScene(const OrthographicCamera &camera);
        static void EndScene();

        // Primitives
        static void DrawQuad(const glm::vec2 &position, const glm::vec2 &size,
                             const glm::vec4 &color);
        static void DrawQuad(const glm::vec3 &position, const glm::vec2 &size,
                             const glm::vec4 &color);
        static void DrawQuad(const glm::vec2 &position, const glm::vec2 &size,
                             const Ref<Texture2D> &texture);
        static void DrawQuad(const glm::vec3 &position, const glm::vec2 &size,
                             const Ref<Texture2D> &texture);
    };
} // namespace Eva
