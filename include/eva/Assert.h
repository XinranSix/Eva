/**
 * @file    :   Assert.h
 * @date    :   2023/06/28 12:14:30
 * @author  :   yaojie
 * @version :   1.0
 */

#pragma once

#include <filesystem>

#ifdef EVA_ENABLE_ASSERTS

	// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
	// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
	#define EVA_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { EVA##type##ERROR(msg, __VA_ARGS__); EVA_DEBUGBREAK(); } }
	#define EVA_INTERNAL_ASSERT_WITH_MSG(type, check, ...) EVA_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define EVA_INTERNAL_ASSERT_NO_MSG(type, check) EVA_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", EVA_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

	#define EVA_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define EVA_INTERNAL_ASSERT_GET_MACRO(...) EVA_EXPAND_MACRO( EVA_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, EVA_INTERNAL_ASSERT_WITH_MSG, EVA_INTERNAL_ASSERT_NO_MSG) )

	// Currently accepts at least the condition and one additional parameter (the message) being optional
	#define EVA_ASSERT(...) EVA_EXPAND_MACRO( EVA_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
	#define EVA_CORE_ASSERT(...) EVA_EXPAND_MACRO( EVA_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
	#define EVA_ASSERT(...)
	#define EVA_CORE_ASSERT(...)
#endif
