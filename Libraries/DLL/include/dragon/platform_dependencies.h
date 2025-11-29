#pragma once

/// @brief specify target platform flags DRAGON_TARGET_WINDOWS and DRAGON_TARGET_POSIX.
#ifdef _WINDOWS_

    #define DRAGON_TARGET_WINDOWS 1
    #define DRAGON_TARGET_POSIX 0

    // Remove annoying Windows macros
    #undef min
    #undef max

#elif defined(__unix__) || defined(__linux__) || defined(__APPLE__)

    #define DRAGON_TARGET_WINDOWS 0
    #define DRAGON_TARGET_POSIX 1
    
    #include <syslog.h>
    #include <locale>
    #include <codecvt>

#else

    #define DRAGON_TARGET_WINDOWS 0
    #define DRAGON_TARGET_POSIX 0

#endif

/// @brief Macro DEBUG is 1 or 0 in release and debug builds, respectively.
#if !defined(DEBUG)
    #if !defined(_DEBUG)
        #define DEBUG 0
    #else
        #define DEBUG 1
    #endif 
#endif 

/// @brief dragon::flags::debug is a constexpr symbol used to indicate a debug build.
/// Used in "if constrexpr..." statements
namespace dragon::flags
{
    // for constexpr constructs
    constexpr bool debug = DEBUG != 0;
}


/// @brief ALWAYS_INLINE macro to indicate [[always_inline]]
/// @note This exists because MSVC is missing the [[always_inline]] attribute
#undef ALWAYS_INLINE
#ifdef _MSC_VER
    // MSVC doesn't yet have [[always_inline]] attribute, so we use __forceinline
    #define ALWAYS_INLINE __forceinline
#else
    #define ALWAYS_INLINE [[always_inline]]
#endif
