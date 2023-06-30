/**
 * @file    :   OpenGLBuffer.h
 * @date    :   2023/06/30 10:45:05
 * @author  :   yaojie
 * @version :   1.0
 */

#pragma once

#include "Buffer.h"

namespace Eva {

    class OpenGLVertexBuffer : public VertexBuffer {
    public:
        OpenGLVertexBuffer(float *vertices, uint32_t size);
        virtual ~OpenGLVertexBuffer();

        virtual void Bind() const;
        virtual void UnBind() const;

    private:
        uint32_t m_RendererID;
    };

    class OpenGLIndexBuffer : public IndexBuffer {
    public:
        OpenGLIndexBuffer(uint32_t *indices, uint32_t count);
        virtual ~OpenGLIndexBuffer();

        virtual void Bind() const;
        virtual void UnBind() const;

        uint32_t GetCount() const { return m_Count; };

    private:
        uint32_t m_RendererID;
        uint32_t m_Count;
    };
} // namespace Eva
