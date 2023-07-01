/**
 * @file    :   OrthographicCamera.cpp
 * @date    :   2023/06/30 22:26:29
 * @author  :   Yao J
 * @version :   1.0
 */

#include <glm/gtc/matrix_transform.hpp>

#include "OrthographicCamera.h"

namespace Eva {

    OrthographicCamera::OrthographicCamera(float left, float right,
                                           float bottom, float top)
        : m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)),
          m_ViewMatrix(1.0f) {
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void OrthographicCamera::RecalulateViewMatrix() {
        glm::mat4 transform =
            glm::translate(glm::mat4(1.0f), m_Position) *
            glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation),
                        glm::vec3(0, 0, 1));

        // FIXME: 此处矩阵应当求逆，但为了方便测试，我这里先不求逆
        // m_ViewMatrix = glm::inverse(transform);
        m_ViewMatrix = transform;
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }
} // namespace Eva
