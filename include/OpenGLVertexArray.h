/**
 * @file    :   OpenGLVertexArray.h
 * @date    :   2023/06/30 14:58:32
 * @author  :   yaojie
 * @version :   1.0
 */

#pragma once

#include <memory>
#include <stdint.h>
#include <vector>

#include "VertexArray.h"

namespace Eva {

    class OpenGLVertexArray : public VertexArray {
    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray();

        virtual void Bind() const override;
        virtual void UnBind() const override;

        virtual void AddVertexBuffer(
            const std::shared_ptr<VertexBuffer> &vertexBuffer) override;
        virtual void SetIndexBuffer(
            const std::shared_ptr<IndexBuffer> &indexBuffer) override;

        virtual const std::vector<std::shared_ptr<VertexBuffer>> &
        GetVertexBuffers() const override {
            return m_VertexBuffers;
        }

        virtual const std::shared_ptr<IndexBuffer> &
        GetIndexBuffers() const override {
            return m_IndexBuffer;
        }

    private:
        uint32_t m_RendererID;
        std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;
    };
} // namespace Eva
