/**
 * @file    :   Log.h
 * @date    :   2023/06/27 16:30:50
 * @author  :   yaojie
 * @version :   1.0
 */

#pragma once

#include <memory>
#include <spdlog/spdlog.h>

namespace Eva {
    class Log {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger> &GetCoreLogger() {
            return s_CoreLogger;
        }

        inline static std::shared_ptr<spdlog::logger> &GetClientLogger() {
            return s_ClientLogger;
        }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
} // namespace GameEngine

// Core Log 宏
#define GE_CORE_TRACE(...) ::Eva::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define GE_CORE_INFO(...) ::Eva::Log::GetCoreLogger()->info(__VA_ARGS__)
#define GE_CORE_WARN(...) ::Eva::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define GE_CORE_ERROE(...) ::Eva::Log::GetCoreLogger()->error(__VA_ARGS__)
#define GE_CORE_FATAL(...) ::Eva::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client Log 宏
#define GE_TRACE(...) ::Eva::Log::GetClientLogger()->trace(__VA_ARGS__)
#define GE_INFO(...) ::Eva::Log::GetClientLogger()->info(__VA_ARGS__)
#define GE_WARN(...) ::Eva::Log::GetClientLogger()->warn(__VA_ARGS__)
#define GE_ERROE(...) ::Eva::Log::GetClientLogger()->error(__VA_ARGS__)
#define GE_FATAL(...) ::Eva::Log::GetClientLogger()->fatal(__VA_ARGS__)
