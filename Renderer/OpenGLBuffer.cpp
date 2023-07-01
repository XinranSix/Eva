/**
 * @file    :   OpenGLBuffer.cpp
 * @date    :   2023/06/30 10:47:42
 * @author  :   Yao J
 * @version :   1.0
 */

#include <glad/glad.h>

#include "OpenGLBuffer.h"

namespace Eva {

    /* ------------------------ OpenGLVertexBuffer Begin ------------------------ */

    OpenGLVertexBuffer::OpenGLVertexBuffer(float *vertices, uint32_t size) {

        glCreateBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer() { glDeleteBuffers(1, &m_RendererID); }

    void OpenGLVertexBuffer::Bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_RendererID); }

    void OpenGLVertexBuffer::UnBind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

    /* ------------------------- OpenGLVertexBuffer End ------------------------- */

    /* ------------------------- OpenGLIndexBuffer Begin ------------------------ */

    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t *indices, uint32_t count) : m_Count(count) {

        glCreateBuffers(1, &m_RendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer() { glDeleteBuffers(1, &m_RendererID); }

    void OpenGLIndexBuffer::Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID); }

    void OpenGLIndexBuffer::UnBind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

    /* -------------------------- OpenGLIndexBuffer End ------------------------- */
} // namespace Eva
