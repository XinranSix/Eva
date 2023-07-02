/**
 * @file    :   Texture.h
 * @date    :   2023/07/01 22:00:18
 * @author  :   Yao J
 * @version :   1.0
 */

#pragma once

#include <stdint.h>
#include <string>
#include <cstdint>

#include "eva/Core.h"

namespace Eva {

    class Texture {
    public:
        virtual ~Texture() = default;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        virtual void SetData(void *data, uint32_t size) = 0;

        virtual void Bind(uint32_t slot = 0) const = 0;
    };

    class Texture2D : public Texture {
    public:
        static Ref<Texture2D> Create(uint32_t width, uint32_t height);
        static Ref<Texture2D> Create(const std::string &path);
    };
} // namespace Eva
