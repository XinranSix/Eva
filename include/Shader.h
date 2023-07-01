/**
 * @file    :   Shader.h
 * @date    :   2023/06/29 22:12:33
 * @author  :   yaojie
 * @version :   1.0
 */

#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Eva {

    class Shader {
    public:
        virtual ~Shader() = default;

        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;

        static Shader *Create(const std::string &vertexSrc,
                              const std::string &fragmentSrc);
    };
} // namespace Eva
