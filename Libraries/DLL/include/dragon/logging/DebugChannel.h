#pragma once

#include <dragon/platform_dependencies.h>

#if DRAGON_TARGET_WINDOWS

#include <dragon/logging/Channel.h>

namespace dragon::logging
{
    /// @brief A logging channel that synchronously outputs messages to the debug console.
    /// 
    /// @details This channel is used for debugging purposes and logs messages to the debug console.
    /// The debug channel is typically used during development to track the flow of execution and debug issues.
    /// It is, by definition, a text only channel, and does not support binary payloads (binary payloads are noted by not recorded).
    class DebugChannel : public BasicChannel
    {
    public:
        DebugChannel(std::string_view name);
        virtual ~DebugChannel();

        void logMessage(
            std::chrono::system_clock::time_point log_time,
            std::string_view subsystem,
            Level level,
            std::string_view message
        ) noexcept override;
    };
}

#endif 
