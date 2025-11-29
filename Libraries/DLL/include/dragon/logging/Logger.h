#pragma once

#include <dragon/events.h>
#include <dragon/logging/Channel.h>
#include <dragon/logging/Level.h>
#include <dragon/platform_dependencies.h>
#include <dragon/strings/unicode.h>
#include <dragon/strings/format.h>
#include <dragon/traits.h>

#include <string>
#include <format>
#include <source_location>

namespace dragon::logging
{
    /// @class Logger
    /// @brief Provides formatted message logging to a specified logging channel for a given subsystem.
    ///
    /// @details The Logger class serves as a facade for categorizing, formatting, and filtering log messages
    ///          directed to a logging channel. It enables structured logging for specific subsystems within an
    ///          application, allowing multiple Logger instances to share the same channel while distinguishing
    ///          their messages by subsystem identifiers. The interface supports formatted string messages,
    ///          similar to the Apple macOS Logger interface for writing interpolated strings.
    ///
    ///          Logger instances can be configured to facilitate contextual logging. Each instance can be 
    ///          bound to another logging channel and assigned a subsystem identifier, which may include hierarchical 
    ///          suffixes for finer-grained categorization (e.g., "application/models/loader").
    class Logger
    {
        std::string subsystem_;
        Level filterLevel_{ Level::none };
        std::shared_ptr<IChannel> channel_;
        events::EventToken filterLevelChangedToken_;
    public:
        Logger();
        Logger(std::shared_ptr<IChannel> channel, std::string_view const subsystem);
        Logger(Logger const& other);
        Logger(Logger const& other, std::string_view const subsystemSuffix);

        explicit Logger(std::string_view const subsystem);

        Logger& operator=(Logger const& other);

        std::string const& subsystem() const noexcept;
        void subsystem(std::string_view subsystem);

        std::shared_ptr<IChannel> channel() const noexcept;
        void channel(std::nullptr_t);
        void channel(std::shared_ptr<IChannel> newChannel);

        bool attached() const noexcept;

        ALWAYS_INLINE Level filterLevel() const noexcept { return filterLevel_; }
        
        ALWAYS_INLINE void log(Level const level, std::string_view message) noexcept {
            if (level >= filterLevel()) {
                logMessage(level, message);
            }
        }

        template <typename... Args>
        ALWAYS_INLINE void log(Level level, std::format_string<Args...> const format, Args&&... args) noexcept {
            if (level >= filterLevel()) {
                if (auto msg{ strings::try_format(format, std::forward<Args>(args)...) }; msg.has_value()) {
                    logMessage(level, msg.value());
                }
                else {
                    DRAGON_ASSERT(false, "Logger::log encountered an unexpected formatting error");
                }
            }
        }

        template <typename... Args>
        ALWAYS_INLINE void alert(std::format_string<Args...> const format, Args&&... args) noexcept {
            log(Level::alert, format, std::forward<Args>(args)...);
        }

        template <typename... Args>
        ALWAYS_INLINE void critical(std::format_string<Args...> const format, Args&&... args) noexcept {
            log(Level::critical, format, std::forward<Args>(args)...);
        }

        template <typename... Args>
        ALWAYS_INLINE void error(std::format_string<Args...> const format, Args&&... args) noexcept {
            log(Level::error, format, std::forward<Args>(args)...);
        }

        template <typename... Args>
        ALWAYS_INLINE void warning(std::format_string<Args...> const format, Args&&... args) noexcept {
            log(Level::warning, format, std::forward<Args>(args)...);
        }

        template <typename... Args>
        ALWAYS_INLINE void notice(std::format_string<Args...> const format, Args&&... args) noexcept {
            log(Level::notice, format, std::forward<Args>(args)...);
        }

        template <typename... Args>
        ALWAYS_INLINE void information(std::format_string<Args...> const format, Args&&... args) noexcept {
            log(Level::information, format, std::forward<Args>(args)...);
        }

        template <typename... Args>
        ALWAYS_INLINE void info(std::format_string<Args...> const format, Args&&... args) noexcept {
            log(Level::information, format, std::forward<Args>(args)...);
        }

        template <typename... Args>
        ALWAYS_INLINE void verbose(std::format_string<Args...> const format, Args&&... args) noexcept {
            log(Level::verbose, format, std::forward<Args>(args)...);
        }

        template <typename... Args>
        ALWAYS_INLINE void debug(std::format_string<Args...> const format, Args&&... args) noexcept {
            if constexpr (dragon::flags::debug) {
                // elided in non-debug builds
                log(Level::debug, format, std::forward<Args>(args)...);
            }
        }

        template <typename... Args>
        ALWAYS_INLINE void trace(std::format_string<Args...> const format, Args&&... args) noexcept {
            if constexpr (dragon::flags::debug) {
                // elided in non-debug builds
                log(Level::trace, format, std::forward<Args>(args)...);
            }
        }

        ALWAYS_INLINE void trace([[maybe_unused]] std::source_location location = std::source_location::current()) noexcept {
            if constexpr (dragon::flags::debug) {
                // elided in non-debug builds
                log(Level::trace, "{}, line:{}", location.file_name(), location.line());
            }
        }

    private:
        void logMessage(Level const level, std::string_view message) noexcept;
    };

}
