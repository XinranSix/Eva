/**
 * @file    :   Buffer.cpp
 * @date    :   2023/06/30 10:35:19
 * @author  :   yaojie
 * @version :   1.0
 */

#include "Buffer.h"
#include "Renderer.h"
#include "eva/Assert.h"
#include "OpenGLBuffer.h"

namespace Eva {

    /* --------------------------- VertexBuffer Begin
     * --------------------------- */

    VertexBuffer *VertexBuffer::Create(float *vertices, uint32_t size) {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::None:
            EVA_CORE_ASSERT(false,
                            "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return new OpenGLVertexBuffer(vertices, size);
        }
        EVA_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }

    /* ---------------------------- VertexBuffer End
     * ---------------------------- */

    /* ---------------------------- IndexBuffer Begin
     * --------------------------- */

    IndexBuffer *IndexBuffer::Create(uint32_t *indices, uint32_t count) {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::None:
            EVA_CORE_ASSERT(false,
                            "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return new OpenGLIndexBuffer(indices, count);
        }
        EVA_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }

    /* ----------------------------- IndexBuffer End
     * ---------------------------- */

} // namespace Eva
