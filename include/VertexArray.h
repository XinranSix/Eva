/**
 * @file    :   VertexArray.h
 * @date    :   2023/06/30 14:50:07
 * @author  :   yaojie
 * @version :   1.0
 */

#pragma once

#include <memory>
#include <vector>

#include "Buffer.h"

namespace Eva {

    class VertexArray {
    public:
        virtual ~VertexArray() {}

        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;

        virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer) = 0;

        virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer) = 0;

        virtual const std::vector<std::shared_ptr<VertexBuffer>> &
        GetVertexBuffers() const = 0;
        virtual const std::shared_ptr<IndexBuffer> &
        GetIndexBuffers() const = 0;

        static VertexArray *Create();
    };

} // namespace Eva