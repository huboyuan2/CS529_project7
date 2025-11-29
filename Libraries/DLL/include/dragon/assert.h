/// @file dragon/assert.h
/// @brief Header file for assertion macros in the Dragon framework.
/// @param cond The condition to assert.
/// @param msg The message to display if the assertion fails.
///
/// @details This header defines the DRAGON_ASSERT macro for debugging purposes.
/// The macro is used to assert conditions during development and debugging.
///
/// When cond is false:
/// 1) emits a message to the debugger on the Windows platform (other to stderr).
/// 2) issues a break command to any attached debugger
///
/// @note Enabled in debug builds by default, but can be disabled by setting the `dragon::assert_enabled` flag to `false`.
/// Disabled in release builds (even when the `dragon::assert_enabled == true`).
#pragma once

#include <dragon/platform_dependencies.h>

#include <cassert>

namespace dragon {
    /// @brief Flag to enable or disable assertions.
    /// @note Ignored in non-debug builds.
    extern bool assert_enabled;
}

#undef DRAGON_ASSERT

#if !defined(_DEBUG)
#define ASSERT(cond, msg)
#elif DRAGON_TARGET_WINDOWS
#include <windows.h>
#define DRAGON_ASSERT(cond, msg) \
        do { \
            if (::dragon::assert_enabled && !(cond)) { \
                OutputDebugStringA(msg); \
                __debugbreak(); \
            } \
        } while(0)
#else
#include <iostream>
#define DRAGON_ASSERT(cond, msg) \
        do { \
            if (::dragon::assert_enabled && !(cond)) { \
                std::cerr << msg << std::endl; \
                assert(false); \
            } \
        } while(0)
#endif
