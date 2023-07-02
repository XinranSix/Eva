/**
 * @file    :   Core.h
 * @date    :   2023/06/27 14:06:31
 * @author  :   Yao J
 * @version :   1.0
 * 核心头文件
 */

#pragma once

#include <memory>

#include "eva.h"

#define BIT(x) (1 << x)

#define EVA_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Eva {

    template<typename T>
    using Scope = std::unique_ptr<T>;
    template<typename T, typename... Args>
    constexpr Scope<T> CreateScope(Args &&...args) {
        return Scope<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Ref = std::shared_ptr<T>;
    template<typename T, typename... Args>
    constexpr Ref<T> CreateRef(Args &&...args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
} // namespace Eva
