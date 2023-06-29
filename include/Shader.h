/**
 * @file    :   Shader.h
 * @date    :   2023/06/29 22:12:33
 * @author  :   yaojie
 * @version :   1.0
 */

#pragma once

#include <string>

namespace Eva {

    class Shader {
    public:
        Shader(const std::string &vertexSrc, const std::string &fragmentSrc);
        ~Shader();

        void Bind() const;
        void UnBind() const;

    private:
        uint32_t m_RendererID;
    };
} // namespace Eva