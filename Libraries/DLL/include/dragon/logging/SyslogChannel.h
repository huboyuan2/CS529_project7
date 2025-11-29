#pragma once

#if DRAGON_TARGET_POSIX

#include <dragon/logging/Channel.h>

namespace dragon::logging
{
    /// @brief A logging channel that synchronously outputs messages to the syslog
    class SyslogChannel : public BasicChannel
    {
    public:
        SyslogChannel(std::string_view name);
        virtual ~SyslogChannel();

        void logMessage(
            std::chrono::system_clock::time_point log_time,
            std::string_view subsystem,
            Level level,
            std::string_view message
        ) noexcept override;
    };
}

#endif
