/**
 * @file    :   Buffer.h
 * @date    :   2023/06/30 10:33:27
 * @author  :   yaojie
 * @version :   1.0
 */

#pragma once

#include <stdint.h>

namespace Eva {

    class VertexBuffer {
    public:
        virtual ~VertexBuffer() {}

        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;

        static VertexBuffer *Create(float *vertices, uint32_t size);
    };

    class IndexBuffer {
    public:
        virtual ~IndexBuffer() {}

        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;

        virtual uint32_t GetCount() const = 0;

        static IndexBuffer *Create(uint32_t *indices, uint32_t size);
    };
} // namespace Eva
