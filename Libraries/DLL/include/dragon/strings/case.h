#pragma once

#include <algorithm>
#include <cctype>
#include <cwctype>
#include <ranges>
#include <string_view>

namespace dragon::strings {

    /// @brief Niebloid to converts a character to lowercase.
    /// 
    /// Supports `char` and `wchar_t`. Other character types such as `char8_t`, `char16_t`, and `char32_t` are not supported.
    /// 
    /// @note This is a custom niebloid: a stateless function object designed for use in range pipelines and views.
    ///       It enables things like `std::views::transform(to_lower)` for case normalization.
    constexpr struct {
        char operator()(char ch) const {
            return static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
        }

        wchar_t operator()(wchar_t ch) const {
            return static_cast<wchar_t>(std::towlower(ch));
        }
    } to_lower;

    /// @brief Range adaptor that transforms characters to lowercase.
    /// 
    /// Can be used with `std::views::transform` to create case-insensitive views.
    /// 
    /// @note This is a view adaptor built from the `to_lower` niebloid.
    ///       It enables expressions like `range | to_lowercase` for lazy transformation.
    constexpr auto to_lowercase = std::views::transform(to_lower);

    namespace case_insensitive {

        /// @brief Compares two ranges for lexicographic equality, ignoring case.
        /// 
        /// Supports `std::string_view`, `std::wstring_view`, and any `string_like_range`.
        /// 
        /// @param a First range.
        /// @param b Second range.
        /// @return true if the ranges are equal ignoring case.
        /// 
        /// @note This is a custom niebloid: it supports overloads for string views and generic ranges.
        ///       Enables ADL-friendly usage like `case_insensitive::equal(a, b)` or in pipelines.
        constexpr struct {
            bool operator()(std::string_view a, std::string_view b) const {
                return std::ranges::equal(a | to_lowercase, b | to_lowercase);
            }

            bool operator()(std::wstring_view a, std::wstring_view b) const {
                return std::ranges::equal(a | to_lowercase, b | to_lowercase);
            }
        } equal;

        /// @brief Checks if the first range starts with the second, ignoring case.
        /// 
        /// Supports `std::string_view`, `std::wstring_view`, and any `string_like_range`.
        /// 
        /// @param a Full range.
        /// @param b Prefix range.
        /// @return true if `a` starts with `b`, ignoring case.
        /// 
        /// @note This is a custom niebloid: it supports overloads for string views and generic ranges.
        ///       Enables usage like `case_insensitive::starts_with(a, b)` in pipelines or conditionals.
        constexpr struct {
            bool operator()(std::string_view a, std::string_view b) const {
                return std::ranges::starts_with(a | to_lowercase, b | to_lowercase);
            }

            bool operator()(std::wstring_view a, std::wstring_view b) const {
                return std::ranges::starts_with(a | to_lowercase, b | to_lowercase);
            }
        } starts_with;

    } // namespace case_insensitive

} // namespace dragon::strings
