/**
 * @file    :   OpenGLTexture.h
 * @date    :   2023/07/01 22:08:47
 * @author  :   Yao J
 * @version :   1.0
 */

#include <stdint.h>

#include "Texture.h"

namespace Eva {

    class OpenGLTexture2D : public Texture2D {
    public:
        OpenGLTexture2D(const std::string &path);
        virtual ~OpenGLTexture2D();

        virtual uint32_t GetWidth() const override { return m_Width; }
        virtual uint32_t GetHeight() const override { return m_Height; }

        virtual void Bind(uint32_t slot) const override;

    private:
        std::string m_Path;
        uint32_t m_Width, m_Height;
        uint32_t m_RendererID;
    };
} // namespace Eva
