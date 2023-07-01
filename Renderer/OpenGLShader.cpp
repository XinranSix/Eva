/**
 * @file    :   OpenGLShader.cpp
 * @date    :   2023/07/01 17:35:04
 * @author  :   yaojie
 * @version :   1.0
 */

#include <glad/glad.h>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "OpenGLShader.h"
#include "Log.h"
#include "eva/Assert.h"

namespace Eva {

    OpenGLShader::OpenGLShader(const std::string &vertexSrc,
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

    OpenGLShader::~OpenGLShader() { glDeleteProgram(m_RendererID); }

    void OpenGLShader::Bind() const { glUseProgram(m_RendererID); }

    void OpenGLShader::UnBind() const { glUseProgram(0); }

    void OpenGLShader::UploadUniformInt(const std::string &name, int value) {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1i(location, value);
    }

    void OpenGLShader::UploadUniformFloat(const std::string &name,
                                          float value) {

        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1f(location, value);
    }

    void OpenGLShader::UploadUniformFloat2(const std::string &name,
                                           const glm::vec2 &value) {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform2f(location, value.x, value.y);
    }

    void OpenGLShader::UploadUniformFloat3(const std::string &name,
                                           const glm::vec3 &value) {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform3f(location, value.x, value.y, value.z);
    }

    void OpenGLShader::UploadUniformFloat4(const std::string &name,
                                           const glm::vec4 &value) {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }

    void OpenGLShader::UploadUniformMat3(const std::string &name,
                                         const glm::mat3 &matrix) {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void OpenGLShader::UploadUniformMat4(const std::string &name,
                                         const glm::mat4 &matrix) {
        GLint location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }
} // namespace Eva
