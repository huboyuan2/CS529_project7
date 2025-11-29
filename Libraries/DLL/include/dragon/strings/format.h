#pragma once

#include <dragon/traits.h>

#include <expected>
#include <format>
#include <iomanip>
#include <optional>

namespace dragon::strings
{
    using namespace std::literals;

    /// @brief Error returned by try_format when formatting fails.
    constexpr struct format_error_t {} format_error;

    /// @brief a noexcept version of std::format, returning a format_error on failure.
    template <typename... Args>
    [[nodiscard("dragon::strings::try_format result cannot be discarded")]]
    inline std::expected<std::string, format_error_t> try_format(std::format_string<Args...> fmt, Args&&... args) noexcept {
        try {
            return std::format(fmt, std::forward<Args>(args)...);
        }
        catch (...) {
            return std::unexpected(format_error);
        }
    }

    /// @brief a noexcept version of std::format, returning a format_error on failure.
    template <typename... Args>
    [[nodiscard("dragon::strings::try_format result cannot be discarded")]]
    inline std::expected<std::wstring, format_error_t> try_format(std::wformat_string<Args...> fmt, Args&&... args) noexcept {
        try {
            return std::format(fmt, std::forward<Args>(args)...);
        }
        catch (...) {
            return std::unexpected(format_error);
        }
    }
    
    /// @brief Provides a string literal for std::nullopt in various character types.
    /// @details This is used to provide a consistent representation of std::nullopt across different character types.
    template <traits::character Char> struct string_literal_nullopt;
    template <> struct string_literal_nullopt<char> { static constexpr auto value = "(nullopt)"sv; };
    template <> struct string_literal_nullopt<wchar_t> { static constexpr auto value = L"(nullopt)"sv; };
    template <> struct string_literal_nullopt<char8_t> { static constexpr auto value = u8"(nullopt)"sv; };
    template <> struct string_literal_nullopt<char16_t> { static constexpr auto value = u"(nullopt)"sv; };
    template <> struct string_literal_nullopt<char32_t> { static constexpr auto value = U"(nullopt)"sv; };
}

namespace std
{
    // Specialization of std::formatter for std::optional<T> to handle formatting of optional values.
    template <typename T, dragon::traits::character Char>
    struct formatter<std::optional<T>, Char> {
        formatter<T, Char> innerFormatter{};

        constexpr auto parse(basic_format_parse_context<Char>& ctx) {
            return innerFormatter.parse(ctx);
        }

        template <typename FormatContext>
        auto format(const std::optional<T>& opt, FormatContext& ctx) const {
            if (opt) {
                return innerFormatter.format(*opt, ctx);
            }
            else {
                return std::format_to(ctx.out(), ::dragon::strings::string_literal_nullopt<Char>::value);
            }
        }
    };

    // Specialization of std::formatter for nullopt_t.
    template <dragon::traits::character Char>
    struct formatter<std::nullopt_t, Char> {
        constexpr auto parse(basic_format_parse_context<Char>& ctx) {
            return ctx.begin();
        }

        template <typename FormatContext>
        auto format(std::nullopt_t, FormatContext& ctx) const {
            return std::format_to(ctx.out(), ::dragon::strings::string_literal_nullopt<Char>::value);
        }
    };
}

