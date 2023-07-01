/**
 * @file    :   OpenGLShader.h
 * @date    :   2023/07/01 17:34:53
 * @author  :   yaojie
 * @version :   1.0
 */

#include <string>
#include <glm/glm.hpp>

#include "Shader.h"

namespace Eva {

    class OpenGLShader : public Shader {
    public:
        OpenGLShader(const std::string &vertexSrc,
                     const std::string &fragmentSrc);
        virtual ~OpenGLShader();

        virtual void Bind() const override;
        virtual void UnBind() const override;

        void UploadUniformInt(const std::string &name,  int value);

        void UploadUniformFloat(const std::string &name,  float value);
        void UploadUniformFloat2(const std::string &name,  const glm::vec2 &value);
        void UploadUniformFloat3(const std::string &name,  const glm::vec3 &value);
        void UploadUniformFloat4(const std::string &name,  const glm::vec4 &value);

             void UploadUniformMat3(const std::string &name,
                               const glm::mat3 &matrix);
        void UploadUniformMat4(const std::string &name,
                               const glm::mat4 &matrix);

    private:
        uint32_t m_RendererID;
    };
} // namespace Eva