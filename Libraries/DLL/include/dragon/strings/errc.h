#pragma once

#include <optional>
#include <string_view>
#include <system_error>

namespace dragon::strings {

    /// @brief determins if the specified std::errc is valid
    bool is_valid(std::errc error) noexcept;

    /// @returns string representation of the specified std::errc, "std::errc::[[invalid]]" when invalid
    std::string_view to_string_view(std::errc error) noexcept;

    /// @overload
    std::wstring_view to_wstring_view(std::errc error) noexcept;

} // namespace dragon::strings

/// @brief std::format support for std::errc
namespace std {
    template <> struct formatter<std::errc, char> : formatter<std::string_view, char> {
        template <class FormatContext> constexpr auto format(std::errc error, FormatContext &ctx) const {
            return formatter<std::string_view, char>::format(dragon::strings::to_string_view(error), ctx);
        }
    };

    template <> struct formatter<std::errc, wchar_t> : formatter<std::wstring_view, wchar_t> {
        template <class FormatContext> constexpr auto format(std::errc error, FormatContext &ctx) const {
            return formatter<std::wstring_view, wchar_t>::format(dragon::strings::to_wstring_view(error), ctx);
        }
    };
} // namespace std
