#pragma once

#include <dragon/logging/Level.h>
#include <dragon/events.h>
#include <dragon/assert.h>

#include <chrono>
#include <span>
#include <string_view>
#include <string>
#include <variant>

namespace dragon::logging
{
    /// @brief Abstraction for a logging channel.
    struct IChannel
    {
        /// @brief Virtual destructor to ensure proper cleanup in derived classes.
        virtual ~IChannel() = 0;

        /// @brief Gets the name of the channel.
        /// @return The name of the channel as a string view.
        virtual std::string_view name() const noexcept = 0;

        /// @brief Gets the current message filtering level for this channel.
        /// @return The current logging level.
        virtual Level filterLevel() const noexcept = 0;

        /// @brief Sets the current message filtering level for this channel.
        virtual void filterLevel(Level newFilterLevel) noexcept = 0;

        /// @brief Event arguments for the FilterLevelChanged event.
        /// @details Contains the old and new filter levels.
        struct FilterLevelChangedEventArguments
        {
            Level oldLevel;    ///< The previous filter level.
            Level newLevel;    ///< The new filter level.
        };
        
        /// @brief Event handler type for FilterLevelChanged events.
        /// @param sender The channel that raised the event.
        /// @param args The event arguments containing the old and new filter levels.
        using FilterLevelChangedHandler = events::EventHandler<IChannel const&, FilterLevelChangedEventArguments const&>;

        /// @brief Registers an event handler to be called when the filter level changes.
        /// @param handler The handler to be called when the filter level changes.
        /// @return An EventToken that can be used to unregister the handler.
        virtual events::EventToken filterLevelChanged(FilterLevelChangedHandler&& handler) = 0;

        /// @brief Unregisters a previously registered FilterLevelChanged handler.
        /// @param token The token previously returned by FilterLevelChanged(handler).
        virtual void filterLevelChanged(events::EventToken const& token) = 0;

        /// @brief Logs a message to the channel with the specified subsystem and logging level.
        /// @note This method must be thread-safe (not checkable at compile time).
        /// @param log_time The date/time of the message.
        /// @param subsystem A string specifying the subsystem for the message.
        /// @param level The logging level at which to log the message.
        /// @param message The message to log.
        virtual void logMessage(
            std::chrono::system_clock::time_point log_time,
            std::string_view subsystem,
            Level level,
            std::string_view message
        ) noexcept = 0;        

        /// @brief Logs a raw buffer to the channel with the specified subsystem and logging level.
        /// @note This method must be thread-safe (not checkable at compile time).
        /// @param log_time The date/time of the message.
        /// @param subsystem A string specifying the subsystem for the message.
        /// @param level The logging level at which to log the buffer.
        /// @param buffer A span representing the raw buffer data to log.
        virtual void logBuffer(
            std::chrono::system_clock::time_point log_time,
            std::string_view subsystem,
            Level level,
            std::span<const std::byte> buffer
        ) noexcept = 0;
    };

    // Base class for logging channels that provides common functionality.
    class BasicChannel : public IChannel
    { 
        std::string const name_;
        Level filterLevel_;
        events::Event<IChannel const&, FilterLevelChangedEventArguments const&> filterLevelChangedEvent_;

    protected:
        BasicChannel(std::string_view name, Level initialFilterLevel = Level::debug);

    public:
        ~BasicChannel() override = default;

        std::string_view name() const noexcept override;
        
        Level filterLevel() const noexcept override;
        void filterLevel(Level newFilterLevel) noexcept override;
        events::EventToken filterLevelChanged(FilterLevelChangedHandler&& handler) override;
        void filterLevelChanged(events::EventToken const& token) override;

        void logMessage(
            std::chrono::system_clock::time_point log_time,
            std::string_view subsystem,
            Level level,
            std::string_view message
        ) noexcept override;

        void logBuffer(
            std::chrono::system_clock::time_point log_time,
            std::string_view subsystem,
            Level level,
            std::span<const std::byte> buffer
        ) noexcept override;

    protected:
        /// @brief Formats a log entry into a human-readable string.
        /// 
        /// This virtual method constructs a formatted message string from the
        /// provided logging elements. It may be overridden to customize output
        /// formats (e.g., JSON, CSV, plain text) or to suppress messages based
        /// on subsystem, severity, or content.
        /// 
        /// @param utc_event_time the UTC timestamp of the logging event
        /// @param subsystem A short identifier for the originating subsystem (e.g., "network", "audio", "physics").
        /// @param level The severity level of the message (e.g., Info, Warning, Error).
        /// @param message The raw message content to be formatted.
        /// @param withNewline requests a newline character at the end of the result; default false
        /// 
        /// @return A formatted string suitable for logging output.
        /// Return a std::nullopt to supress the even from the log.
        /// 
        /// @note derived implementations should be writted to be thread-safe on this object
        virtual std::optional<std::string> formatMessage(
            std::chrono::utc_clock::time_point utc_event_time,
            std::string_view subsystem,
            Level level,
            std::string_view message,
            bool withNewline = false
        ) const;
    };
}
