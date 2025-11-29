#pragma once

#include <dragon/strings/unicode.h>

#include <cctype>
#include <cwctype>

namespace dragon::strings {

    /// @brief Neibloid to check if a character is whitespace
    struct is_whitespace_t {
        
        /// @brief indicates whether the specified char is whitespace
        bool operator()(char ch) const {
            return std::isspace(ch);
        }

        /// @brief indicates whether the specified wchar_t is whitespace
        bool operator()(wchar_t ch) const {
            return std::iswspace(ch);
        }

        /// @brief indicates whether the specified unicode char16_t is whitespace
        bool operator()(char16_t ch) const {
            return unicode::is_whitespace(ch);
        }

        /// @brief indicates whether the specified unicode char32_t code point is whitespace
        bool operator()(char32_t ch) const {
            return unicode::is_whitespace(ch);
        }
    };
    constexpr is_whitespace_t is_whitespace;




} 
