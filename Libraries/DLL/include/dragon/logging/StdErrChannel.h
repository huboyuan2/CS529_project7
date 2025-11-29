#pragma once

#include <dragon/logging/Channel.h>

namespace dragon::logging
{
    /// @brief A logging channel that synchronously outputs messages to std::err
    class StdErrChannel : public BasicChannel {
    public:
        StdErrChannel(std::string_view name);

        void logMessage(
            std::chrono::system_clock::time_point log_time,
            std::string_view subsystem,
            Level level,
            std::string_view message
        ) noexcept override;
    };
}
