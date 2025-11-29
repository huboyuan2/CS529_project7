#pragma once

#include <dragon/logging/Channel.h>

#include <mutex>
#include <vector>

namespace dragon::logging
{
    /// @brief A logging channel that multiplexes messages to a primary channel and additional secondary channels.
    class MultiplexChannel : public IChannel
    {
    public:
        /// @brief Constructs a MultiplexChannel with a primary channel.
        /// @param primaryChannel The primary channel to which all messages will be sent.
        MultiplexChannel(std::shared_ptr<IChannel> primaryChannel);

        /// @brief Adds a secondary channel to the MultiplexChannel.
        /// @param channel The secondary channel to add.
        void addChannel(std::shared_ptr<IChannel> channel);

        /// @brief Removes a secondary channel from the MultiplexChannel.
        /// @param channel The secondary channel to remove.
        void removeChannel(std::shared_ptr<IChannel> channel);

        /// @brief Gets the primary channel of the MultiplexChannel.
        std::shared_ptr<IChannel> primaryChannel() const noexcept;
        
        // These IChannel interface methods dispatched to the primary channel
        std::string_view name() const noexcept override;
        Level filterLevel() const noexcept override;
        void filterLevel(Level newFilterLevel) noexcept override;
        events::EventToken filterLevelChanged(FilterLevelChangedHandler&& handler) override;
        void filterLevelChanged(events::EventToken const& token) override;

        // Logging methods that dispatch to the primary channel and echo to secondary channels
        virtual void logMessage(
            std::chrono::system_clock::time_point log_time,
            std::string_view subsystem,
            Level level,
            std::string_view message
        ) noexcept override;

        // Logs a raw buffer to the primary channel and echoes it to secondary channels.
        virtual void logBuffer(
            std::chrono::system_clock::time_point log_time,
            std::string_view subsystem,
            Level level,
            std::span<const std::byte> buffer
        ) noexcept override;
    private:
        std::shared_ptr<IChannel> primaryChannel_;
        std::mutex secondaryChannelsMutex_;
        std::vector<std::shared_ptr<IChannel>> secondaryChannels_;
    };

}
