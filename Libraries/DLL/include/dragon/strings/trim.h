#pragma once

#include <dragon/traits.h>
#include <dragon/strings/categories.h>

#include <functional>
#include <ranges>
#include <string_view>

namespace dragon::strings {

    namespace implementation {
        // helper for strings::drop_prefix
        template <typename Char, typename CharTraits>
        inline std::basic_string_view<Char, CharTraits> drop_prefix(std::basic_string_view<Char, CharTraits> str,
                                                                    std::basic_string_view<Char, CharTraits> prefix) {
            if (str.starts_with(prefix)) {
                str.remove_prefix(prefix.size());
            }
            return str;
        }

        // helper for strings::drop_first_prefix
        template <typename StringView, typename Prefixes>
        StringView drop_first_prefix(StringView str, Prefixes const& prefixes) {
            for (StringView prefix : prefixes) {
                if (str.starts_with(prefix)) {
                    return str.substr(prefix.size());
                }
            }
            return str;
        }

        // helper for strings::drop_longest_prefix
        template <typename StringView, typename Prefixes>
        inline StringView drop_longest_prefix(StringView str, Prefixes prefixes) {
            StringView candidate{};
            for (StringView prefix : prefixes) {
                if (prefix.length() > candidate.length() && str.starts_with(prefix)) {
                    candidate = prefix;
                }
            }
            return str.substr(candidate.length());
        }

        // helper for strings::drop_suffix
        template <typename Char, typename CharTraits>
        inline auto drop_suffix(std::basic_string_view<Char, CharTraits> str,
                                std::basic_string_view<Char, CharTraits> suffix) {
            if (str.ends_with(suffix)) {
                str.remove_suffix(suffix.size());
            }
            return str;
        }

    }

    /// @brief removes the prefix from the specified string view if present
    /// @param str the string view to search
    /// @param prefix the string view to remove if present
    /// @return str sans the leading prefix if present
    inline auto drop_prefix(std::string_view str, std::string_view prefix) {
        return implementation::drop_prefix(str, prefix);
    }

    /// @overload
    inline auto drop_prefix(std::wstring_view str, std::wstring_view prefix) {
        return implementation::drop_prefix(str, prefix);
    }

    /// @overload
    inline auto drop_prefix(std::u8string_view str, std::u8string_view prefix) {
        return implementation::drop_prefix(str, prefix);
    }

    /// @overload
    inline auto drop_prefix(std::u16string_view str, std::u16string_view prefix) {
        return implementation::drop_prefix(str, prefix);
    }

    /// @overload
    inline auto drop_prefix(std::u32string_view str, std::u32string_view prefix) {
        return implementation::drop_prefix(str, prefix);
    }

    /// @brief removes the first prefix found in str
    /// @param str the string view to search
    /// @param prefixes the ordered list of strings, the first of which that appears as a prefix of str will be removed
    /// @return str sans the first matching prefix
    template <typename Prefixes>
    auto drop_first_prefix(std::string_view str, Prefixes const& prefixes) {
        return implementation::drop_first_prefix(str, prefixes);
    }

    /// @overload
    template <typename Prefixes>
    auto drop_first_prefix(std::wstring_view str, Prefixes const& prefixes) {
        return implementation::drop_first_prefix(str, prefixes);
    }

    /// @overload
    template <typename Prefixes>
    auto drop_first_prefix(std::u8string_view str, Prefixes const& prefixes) {
        return implementation::drop_first_prefix(str, prefixes);
    }

    /// @overload
    template <typename Prefixes>
    auto drop_first_prefix(std::u16string_view str, Prefixes const& prefixes) {
        return implementation::drop_first_prefix(str, prefixes);
    }

    /// @overload
    template <typename Prefixes>
    auto drop_first_prefix(std::u32string_view str, Prefixes const& prefixes) {
        return implementation::drop_first_prefix(str, prefixes);
    }

    /// @brief removes the longest prefix found in str
    /// @param str the string view to search
    /// @param prefixes to search through
    /// @return str sans the longest matching prefix
    template <typename Prefixes>
    auto drop_longest_prefix(std::string_view str, Prefixes const &prefixes) {
        return implementation::drop_longest_prefix(str, prefixes);
    }

    /// @overload
    template <typename Prefixes>
    auto drop_longest_prefix(std::wstring_view str, Prefixes const &prefixes) {
        return implementation::drop_longest_prefix(str, prefixes);
    }

    /// @overload
    template <typename Prefixes>
    auto drop_longest_prefix(std::u8string_view str, Prefixes const &prefixes) {
        return implementation::drop_longest_prefix(str, prefixes);
    }

    /// @overload
    template <typename Prefixes>
    auto drop_longest_prefix(std::u16string_view str, Prefixes const &prefixes) {
        return implementation::drop_longest_prefix(str, prefixes);
    }

    /// @overload
    template <typename Prefixes>
    auto drop_longest_prefix(std::u32string_view str, Prefixes const &prefixes) {
        return implementation::drop_longest_prefix(str, prefixes);
    }

    /// @brief Drops a specified suffix from a string view if present
    /// @param str the string to scan
    /// @param suffix the suffix to drop if present
    /// @return str sans the suffix, if present
    inline auto drop_suffix(std::string_view str, std::string_view suffix) {
        return implementation::drop_suffix(str, suffix);
    }

    /// @overload
    inline auto drop_suffix(std::wstring_view str, std::wstring_view suffix) {
        return implementation::drop_suffix(str, suffix);
    }

    /// @overload
    /// @note presumed that str and suffix are well-formed UTF-8 sequences
    inline auto drop_suffix(std::u8string_view str, std::u8string_view suffix) {
        return implementation::drop_suffix(str, suffix);
    }

    /// @overload
    /// @note presumed that str and suffix are well-formed UTF-16 sequences
    inline auto drop_suffix(std::u16string_view str, std::u16string_view suffix) {
        return implementation::drop_suffix(str, suffix);
    }

    /// @overload
    inline auto drop_suffix(std::u32string_view str, std::u32string_view suffix) {
        return implementation::drop_suffix(str, suffix);
    }

    
    /// @brief View adaptor to filter out whitespace characters
    constexpr auto sans_whitespace = std::views::filter(std::not_fn(is_whitespace));

    /// @brief View adaptor to drop leading whitespace characters
    constexpr auto drop_whitespace = std::views::drop_while(is_whitespace);

    /// @brief Trims leading whitespace from a string view
    /// @param str The input string view
    /// @return str sans leading whitespace
    inline auto trim_leading_whitespace(std::string_view str) {
        return std::string_view{str | drop_whitespace};
    }

    /// @overload
    inline auto trim_leading_whitespace(std::wstring_view str) {
        return std::wstring_view{str | drop_whitespace};
    }

    /// @overload
    inline auto trim_leading_whitespace(std::u8string_view str) {
        return unicode::drop_leading_whitespace(str);
    }

    /// @overload
    inline auto trim_leading_whitespace(std::u16string_view str) {
        return unicode::drop_leading_whitespace(str);
    }

    /// @overload
    inline auto trim_leading_whitespace(std::u32string_view str) {
        return unicode::drop_leading_whitespace(str);
    }

    /// @brief Trims trailing whitespace from a string view
    /// @param str The input string view
    /// @return String view with trailing whitespace removed
    inline auto trim_trailing_whitespace(std::string_view str) {
        using std::views::reverse;
        return str.substr(0, (reverse(str) | drop_whitespace).size());
    }

    /// @overload
    inline auto trim_trailing_whitespace(std::wstring_view str) {
        using std::views::reverse;
        return str.substr(0, (reverse(str) | drop_whitespace).size());
    }

    /// @overload
    inline auto trim_trailing_whitespace(std::u8string_view str) {
        return unicode::drop_trailing_whitespace(str);
    }

    /// @overload
    inline auto trim_trailing_whitespace(std::u16string_view str) {
        return unicode::drop_trailing_whitespace(str);
    }

    /// @overload
    inline auto trim_trailing_whitespace(std::u32string_view str) {
        return unicode::drop_trailing_whitespace(str);
    }

    /// @brief Trims both leading and trailing whitespace from a string view
    /// @param str The input string view
    /// @return String view with leading and trailing whitespace removed
    inline auto trim_whitespace(std::string_view str) {
        return trim_trailing_whitespace(trim_leading_whitespace(str));
    }

    /// @overload
    inline auto trim_whitespace(std::wstring_view str) {
        return trim_trailing_whitespace(trim_leading_whitespace(str));
    }

    /// @overload
    inline auto trim_whitespace(std::u8string_view str) {
        return trim_trailing_whitespace(trim_leading_whitespace(str));
    }

    /// @overload
    inline auto trim_whitespace(std::u16string_view str) {
        return trim_trailing_whitespace(trim_leading_whitespace(str));
    }

    /// @overload
    inline auto trim_whitespace(std::u32string_view str) {
        return trim_trailing_whitespace(trim_leading_whitespace(str));
    }

}
