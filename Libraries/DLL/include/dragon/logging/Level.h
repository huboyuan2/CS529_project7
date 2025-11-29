#pragma once

#include <string_view>
#include <format>

namespace dragon::logging
{
    /// @enum Level
    /// @brief Defines severity levels for logging output.
    ///
    /// Used to categorize messages by importance and urgency.
    /// These levels guide filtering and formatting behavior across platforms.
    enum class Level
    {
        /// @brief Specifies a filter level that allows all message write attempts.
        all = -3,

        /// @brief Indicates a debug-only message with detailed information, possibly including sensitive data.
        ///
        /// @details These messages may include sensitive information like customer preferences, IDs, and source locations.
        /// They are disabled by default and are never permitted in release builds.
        trace,

        /// @brief Indicates a message useful during development for debugging or QA testing.
        ///
        /// @details These logs should primarily contain information useful for debugging and have no long-term value.
        /// No sensitive information should be recorded in debug messages. These messages are disabled by default in release builds.
        debug,

        /// @brief Indicates a message recording important state information during normal program operation.
        ///
        /// @details For example, recording search terms and a count of initial results. Verbose messaging is useful
        /// when recording information that provides context leading up to an error but may not be directly related
        /// to the error condition.
        verbose,

        /// @brief Indicates a message about a program event or state change.
        ///
        /// @details For example, a user authorization attempt may be logged with an information level along with
        /// messaging indicating failure or success. Messages logged at this level should be purely informative, and
        /// not regularly reviewing them should not result in missing important functional information.
        information,

        /// @brief Indicates a message about an event that is normal but may require attention.
        notice, 

        /// @brief Indicates an unexpected problem or situation that might degrade program performance or functionality.
        ///
        /// @details For example, a parser error that resulted in a document not being processed properly.
        warning,

        /// @brief Indicates non-critical errors that may prevent some functionalities from operating properly.
        error,

        /// @brief Indicates critical faults or bugs causing crucial functionalities to fail, often leading to termination.
        critical,

        /// @brief Indicates a critical failure for which action must be taken immediately 
        /// (typically only used with syslog logging).
        alert,

        /// @brief Specifies a filter level that blocks all message write attempts.
        none
    };

    /// @brief Converts a logging::Level to std::string_view.
    ///
    /// @param level The logging level to convert.
    /// @return A std::string_view representing the level.
    std::string_view to_string_view(Level level) noexcept;

    /// @brief Converts a logging::Level to std::wstring_view.
    ///
    /// @param level The logging level to convert.
    /// @return A std::wstring_view representing the level.
    std::wstring_view to_wstring_view(Level level) noexcept;
}

/// @brief std::format support for dragon::logging::Level.
namespace std
{
    template<>
    struct formatter<dragon::logging::Level, char> : formatter<std::string_view, char>
    {
        template<class FormatContext>
        constexpr auto format(dragon::logging::Level level, FormatContext& ctx) const
        {
            return formatter<std::string_view, char>::format(dragon::logging::to_string_view(level), ctx);
        }
    };

    template<>
    struct formatter<dragon::logging::Level, wchar_t> : formatter<std::wstring_view, wchar_t>
    {
        template<class FormatContext>
        constexpr auto format(dragon::logging::Level level, FormatContext& ctx) const
        {
            return formatter<std::wstring_view, wchar_t>::format(dragon::logging::to_wstring_view(level), ctx);
        }
    };
}
