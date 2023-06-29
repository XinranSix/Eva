/**
 * @file    :   Shader.cpp
 * @date    :   2023/06/29 22:13:33
 * @author  :   yaojie
 * @version :   1.0
 */

#include "Shader.h"
#include "Log.h"
#include "eva/Assert.h"

#include <glad/glad.h>
#include <vector>

namespace Eva {

    Shader::Shader(const std::string &vertexSrc,
                   const std::string &fragmentSrc) {
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

        const GLchar *source = (const GLchar *)vertexSrc.c_str();
        glShaderSource(vertexShader, 1, &source, 0);
        glCompileShader(vertexShader);

        GLint isCompiled = 0;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE) {
            GLint maxLength = 0;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(vertexShader, maxLength, &maxLength,
                               &infoLog[0]);
            glDeleteShader(vertexShader);

            EVA_CORE_ERROE("Vertex shader compilation failure!");
            EVA_CORE_ERROE("{0}", infoLog.data());
            EVA_CORE_ASSERT(false, "Vertex shader compilation failure!");
            return;
        }

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        source = (const GLchar *)fragmentSrc.c_str();
        glShaderSource(fragmentShader, 1, &source, 0);
        glCompileShader(fragmentShader);
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);

        if (isCompiled == GL_FALSE) {
            GLint maxLength = 0;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(fragmentShader, maxLength, &maxLength,
                               &infoLog[0]);
            glDeleteShader(fragmentShader);

            EVA_CORE_ERROE("Fragment shader compilation failure!");
            EVA_CORE_ERROE("{0}", infoLog.data());
            EVA_CORE_ASSERT(false, "Fragment shader compilation failure!");
            return;
        }

        m_RendererID = glCreateProgram();
        GLuint program = m_RendererID;

        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);

        glLinkProgram(program);

        GLint isLinked = 0;

        glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
        if (isLinked == GL_FALSE) {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);

            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

            glDeleteProgram(program);

            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            EVA_CORE_ERROE("Shader link failure!");
            EVA_CORE_ERROE("{0}", infoLog.data());
            EVA_CORE_ASSERT(false, "Shader link failure!");
            return;
        }
        glDetachShader(program, vertexShader);
        glDetachShader(program, fragmentShader);
    }

    Shader::~Shader() { glDeleteProgram(m_RendererID); }

    void Shader::Bind() const { glUseProgram(m_RendererID); }

    void Shader::UnBind() const { glUseProgram(0); }
} // namespace Eva
