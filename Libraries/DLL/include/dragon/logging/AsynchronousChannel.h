#pragma once

#include <dragon/logging/Channel.h>

#include <condition_variable>
#include <memory>

namespace dragon::logging {

    class AsynchronousChannel : public BasicChannel
    {
    public:
        /// @brief Constructs an AsynchronousChannel with a specified channel.
        /// @param channel The channel to which log messages will be sent asynchronously.
        /// @note will fault if channel is nullptr.
        AsynchronousChannel(std::shared_ptr<IChannel> channel);
        virtual ~AsynchronousChannel();

        void logMessage(
            std::chrono::system_clock::time_point log_time,
            std::string_view subsystem,
            Level level,
            std::string_view message
        ) noexcept override;

    private:
        void processMessages(std::stop_token stopToken);

        struct Message {
            std::chrono::system_clock::time_point dateTime;
            std::string subsystem;
            Level level;
            std::string message;

            Message(
                std::chrono::system_clock::time_point dt,
                std::string_view sub,
                Level lvl,
                std::string_view msg
            ) : dateTime(dt), subsystem(sub), level(lvl), message(msg) {
            }
        };

        struct MessageQueue : std::vector<Message> { 
            explicit MessageQueue(size_t capacity) { reserve(capacity); }
        };

        MessageQueue messages_;
        std::mutex mutex_;
        std::condition_variable_any condition_;
        std::shared_ptr<IChannel> channel_;

        // declared last to ensure it's constructed last and destructed first
        std::jthread thread_;
    };
}
