/**
 * @file    :   Log.cpp
 * @date    :   2023/06/27 16:30:53
 * @author  :   Yao J
 * @version :   1.0
 */

#include "Log.h"
#include "eva/Core.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Eva {

    void Log::Init() {
        spdlog::set_pattern("%^[%T] %n: %v%$");

        s_CoreLogger = spdlog::stdout_color_mt("Eva");
        s_CoreLogger->set_level(spdlog::level::trace);

        s_ClientLogger = spdlog::stdout_color_mt("APP");
        s_ClientLogger->set_level(spdlog::level::trace);
    }

    Ref<spdlog::logger> Log::s_CoreLogger;
    Ref<spdlog::logger> Log::s_ClientLogger;
} // namespace GameEngine
