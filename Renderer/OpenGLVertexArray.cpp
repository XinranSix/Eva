/**
 * @file    :   OpenGLVertexArray.cpp
 * @date    :   2023/06/30 14:58:55
 * @author  :   Yao J
 * @version :   1.0
 */

#include <glad/glad.h>

#include "eva/Core.h"
#include "OpenGLVertexArray.h"

namespace Eva {

    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
        switch (type) {
        case ShaderDataType::Float:
            return GL_FLOAT;
        case ShaderDataType::Float2:
            return GL_FLOAT;
        case ShaderDataType::Float3:
            return GL_FLOAT;
        case ShaderDataType::Float4:
            return GL_FLOAT;
        case ShaderDataType::Mat3:
            return GL_FLOAT;
        case ShaderDataType::Mat4:
            return GL_FLOAT;
        case ShaderDataType::Int:
            return GL_INT;
        case ShaderDataType::Int2:
            return GL_INT;
        case ShaderDataType::Int3:
            return GL_INT;
        case ShaderDataType::Int4:
            return GL_INT;
        case ShaderDataType::Bool:
            return GL_BOOL;
        }
        EVA_CORE_ASSERT(false, "UnKnown ShaderDataType!");
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray() {
        glCreateVertexArrays(1, &m_RendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray() {
        glDeleteVertexArrays(1, &m_RendererID);
    }

    void OpenGLVertexArray::Bind() const { glBindVertexArray(m_RendererID); }

    void OpenGLVertexArray::UnBind() const { glBindVertexArray(0); }

    void
    OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer> &vertexBuffer) {

        EVA_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(),
                        "Vertex Buffer has no layout!");

        glBindVertexArray(m_RendererID);
        vertexBuffer->Bind();

        uint32_t index = 0;
        // FIXME: 此处有 Bug，layout 不能是 const 修饰的，也不能是引用，好奇怪。
        // const auto &layout = m_VertexBuffer->GetLayout();
        auto layout = vertexBuffer->GetLayout();

        for (const auto &element : layout) {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, element.GetComponentCount(),
                                  ShaderDataTypeToOpenGLBaseType(element.Type),
                                  element.Normalized ? GL_TRUE : GL_FALSE,
                                  layout.GetStride(),
                                  (const void *)element.Offset);
            ++index;
        }
        m_VertexBuffers.push_back(vertexBuffer);
    }

    void
    OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer> &indexBuffer) {

        glBindVertexArray(m_RendererID);
        indexBuffer->Bind();

        m_IndexBuffer = indexBuffer;
    }

} // namespace Eva
