/**
 * @file    :   OpenGLVertexArray.h
 * @date    :   2023/06/30 14:58:32
 * @author  :   Yao J
 * @version :   1.0
 */

#pragma once

#include <memory>
#include <stdint.h>
#include <vector>

#include "VertexArray.h"
#include "eva/Core.h"

namespace Eva {

    class OpenGLVertexArray : public VertexArray {
    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray();

        virtual void Bind() const override;
        virtual void UnBind() const override;

        virtual void AddVertexBuffer(
            const Ref<VertexBuffer> &vertexBuffer) override;
        virtual void SetIndexBuffer(
            const Ref<IndexBuffer> &indexBuffer) override;

        virtual const std::vector<Ref<VertexBuffer>> &
        GetVertexBuffers() const override {
            return m_VertexBuffers;
        }

        virtual const Ref<IndexBuffer> &
        GetIndexBuffers() const override {
            return m_IndexBuffer;
        }

    private:
        uint32_t m_RendererID;
        std::vector<Ref<VertexBuffer>> m_VertexBuffers;
        Ref<IndexBuffer> m_IndexBuffer;
    };
} // namespace Eva
