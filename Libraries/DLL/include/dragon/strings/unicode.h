/// @file dragon/strings.unicode.h
/// 
/// @details
/// 
/// Unicode has emerged as the universal standard for encoding and exchanging string data. While
/// developers often overlook a string’s encoding, understanding how text sequences are
/// represented is sometimes essential. The era of relying solely on ASCII or UCS-2, where
/// strings were simple sequences of fixed-width characters, has long passed. Whether you’re
/// developing a video game with localized text rendering, implementing a chat feature, or
/// transmitting string data to cloud services, robust support for Unicode Transformation
/// Formats (UTF) is critical. Regrettably, the C++ standard library currently lacks
/// comprehensive built-in support for Unicode, leaving developers to bridge this gap with
/// external libraries or custom solutions.
/// 
/// The C++23 standard's omission of comprehensive Unicode conversion functions stems from a
/// combination of technical, historical, and practical factors. Here's a concise explanation
/// based on the context and available information:
/// 
/// 1) Complexity of Unicode: Unicode is intricate, with evolving standards (e.g., new emoji,
///    scripts) and multiple encoding forms (UTF-8, UTF-16, UTF-32). Designing robust,
///    general-purpose conversion functions that handle all edge cases—such as invalid sequences,
///    surrogate pairs, or bidirectional text—while maintaining performance and safety is
///    challenging. The C++ Standards Committee prioritizes features that can be standardized with
///    clear, portable behavior, and Unicode conversions involve nuances that are hard to codify
///    universally.
/// 
/// 2) Existing Ecosystem: C++ relies heavily on external libraries like ICU, Boost, or
///    platform-specific APIs (e.g., Windows' MultiByteToWideChar) for Unicode handling. These
///    libraries are mature, widely used, and address specific needs (e.g., ICU's comprehensive
///    Unicode support). The committee often avoids duplicating functionality available in
///    established libraries to keep the standard library lean and focused on core language
///    features.
/// 
/// 3) Historical Context: C++'s character handling (char, wchar_t) predates modern Unicode
///    standards, leading to a legacy of platform-dependent encodings (e.g., wchar_t is UTF-16 on
///    Windows but UTF-32 on Linux). Introducing Unicode conversion functions would require
///    reconciling these differences, potentially breaking backward compatibility or requiring
///    complex abstractions. Earlier attempts, like codecvt in C++11, were deprecated in C++17 due
///    to design flaws and insufficient generality.
/// 
/// 4) Committee Priorities: The C++23 cycle focused on features like modules, ranges, and
///    concurrency improvements. Proposals for Unicode support (e.g., P1629 for text encoding)
///    exist but face challenges in reaching consensus due to scope creep or incomplete
///    specifications. Standardization requires rigorous testing and agreement, which takes time,
///    especially for a domain as broad as Unicode.
/// 
/// 5) Practical Considerations: Developers can use libraries like ICU or implement custom
///    solutions, as seen in your UTF-8/UTF-16 codepoint view code. The committee may view this as
///    sufficient for now, allowing flexibility for domain-specific needs rather than mandating a
///    one-size-fits-all solution.
/// 
/// Without standard Unicode conversion functions, developers must rely on external libraries or
/// custom code, leading to potential inconsistencies or portability issues. However, the
/// committee's cautious approach ensures that any standardized solution will be robust and
/// widely applicable.
/// 
/// Developers have long awaited native Unicode support in the C++ standard library, and the absence
/// of idiomatic Unicode conversion functions in C++23 remains a pain point. The ICU library, while
/// comprehensive, has drawbacks due to its C-style idioms, which clash with modern C++ practices
/// (e.g., RAII, type safety, views, and ranges). This makes integration into C++ projects cumbersome,
/// especially for developers accustomed to the standard library's conventions.
/// 
/// This header provides minimal, idiomatic primitives for Unicode handling in C++23.
/// It is not exhaustive, but sufficient for common decoding, validation, and conversion tasks.
/// 
/// Includes:
///  - Utf8CodePointView and Utf16CodePointView for range-based iteration of codepoints
///  - error-aware decoding via std::expected<char32_t, std::errc>
///  - conversion utilities between UTF-8, UTF-16, and UTF-32
/// 
/// All decoding functions are error-aware and return std::expected<char32_t, std::errc>,
/// enabling precise handling of invalid sequences and empty ranges.
/// 
/// Future standardization efforts (e.g., P1629: std::text_encoding) may eventually
/// address Unicode conversions. This code offers a pragmatic interim solution.
#pragma once

#include <dragon/traits.h>

#include <exception>
#include <string>
#include <string_view>
#include <expected>
#include <span>

namespace dragon::strings {

    /// @brief the dragon::strings::unicode namespace contains low level primitives
    /// for processing unicode codepoints.  Typically, these are not directly used in applications.
    namespace unicode {

        /// @brief a view of code points over an underlying view of characters.
        /// Provides a way to lazily enumerate code points in a unicode encoded string.
        /// 
        /// @code
        /// // example iteration of the codepoints in a string
        /// std::string_view utf8 = "ℒōřęm īƥşūм"; // unicode string with multi-character codepoints
        /// for (char32_t cp : code_points(utf8)) {
        ///     // process each code point
        /// }
        /// @endcode
        template <traits::any_of<char8_t, char16_t, char32_t> Char>
        class CodePointView { // : public std::ranges::view_interface<CodePointView<Char>> {
        public:
            using string_view = std::basic_string_view<Char>;

            CodePointView() = default;
            CodePointView(CodePointView&&) = default;
            CodePointView(CodePointView const&) = default;
            CodePointView& operator=(CodePointView const&) = default;

            /// @brief Constructs a CodePointView from a string view.
            /// @param source The input string view containing encoded text.
            explicit CodePointView(string_view source) : source_{ source } {
                if (!source_.empty()) {
                    computeFront();
                }                
            }

            /// @brief Checks if the CodePointView is empty.
            /// @return True if the view is empty, false otherwise.
            bool empty() const noexcept { return source_.empty(); }

            /// @brief Retrieves the first code point.
            /// @return The first UTF-8 code point as a char32_t.
            /// @throws std::out_of_range If the view is empty.
            /// @throws std::system_error If the sequence is invalid.
            char32_t front() const {
                if (empty()) {
                    throw std::out_of_range("CodePointView::front: empty range");
                }
                if (front_.has_value()) {
                    return front_.value();
                }
                throw std::system_error(std::make_error_code(front_.error()), "CodePointView::front: invalid character sequence");
            }

            /// @brief Advances the view to the next code point.
            /// @throws std::out_of_range If the view is empty.
            /// @throws std::system_error If the sequence is invalid.
            void pop_front() {
                if (empty()) {
                    throw std::out_of_range("CodePointView::front: empty range");
                }
                // already in an error state
                if (!front_.has_value()) {
                    throw std::system_error(std::make_error_code(front_.error()), "CodePointView::front: invalid character sequence");
                }
                // otherwise advance and compute the next front
                source_ = next_;
                if (!next_.empty()) {
                    computeFront();
                }                
            }

            /// @brief returns the source string_view of this CodePointView
            string_view source() const noexcept { return source_; }

            /// @brief checks two CodePointViews for equality
            bool operator==(CodePointView const& other) const noexcept {
                // equal iff they have identical source sequences
                return source_ == other.source_;
            }

            /// @brief checks two CodePointViews for inequality
            bool operator!=(CodePointView const& other) const noexcept {
                // equal iff they have identical source sequences
                return source_ != other.source_;
            }

            /// @brief C++ iteration support
            class sentinel {};
            class iterator {
            public:
                using iterator_category = std::forward_iterator_tag; // Forward iterator for multi-pass
                using value_type = char32_t;
                using difference_type = std::ptrdiff_t;
                using pointer = const char32_t*;
                using reference = char32_t;

                iterator() = default;
                explicit iterator(CodePointView view) : view_(view) {}

                char32_t operator*() const { return view_.front(); }
                iterator& operator++() { view_.pop_front(); return *this; }
                iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }

                // only permit comparison to the sentinel
                bool operator==(sentinel) const {
                    return view_.empty();
                }

            private:
                CodePointView view_; // Holds a copy for forward semantics
            };

            auto begin() const { return iterator(*this); }
            sentinel end() const { return sentinel{}; }
            auto cbegin() const { return iterator(*this); }
            sentinel cend() const { return sentinel{}; }

        private:
            friend class iterator;
            void computeFront() noexcept;

            std::expected<char32_t, std::errc> front_;
            string_view source_;
            string_view next_;
        };

        /// @note computeFront is specialized and defined in unicode.cpp 
        template <> void CodePointView<char8_t>::computeFront() noexcept;
        template <> void CodePointView<char16_t>::computeFront() noexcept;
        template <> void CodePointView<char32_t>::computeFront() noexcept;

        /// @brief Function adapter for constructing the correct CodePointView based on the input type.
        /// 
        /// @tparam dummy Dummy template parameter to allow SFINAE-friendly overload resolution.
        /// This is because in C++23 templates are necessary to employ requires clauses.
        /// As with neibloids, the downside of this approach is that the symbol `code_points`
        /// cannot be overloaded elsewhere.
        /// 
        /// @note For `std::string_view`, the input is assumed to contain UTF-8 encoded data.
        ///       For `std::wstring_view`, reinterpretation depends on the platform's `wchar_t` size.
        /// 
        /// @code
        /// std::wstring_view utf16 = L"ℒōřęm īƥşūм";
        /// for (char32_t cp : unicode::code_points(utf16)) {
        ///     // process each code point
        /// }
        /// @endcode
        template <typename dummy = int>
        struct code_points_t {
            inline auto operator()(std::u8string_view str) const {
                return CodePointView<char8_t>(str);
            }

            inline auto operator()(std::u16string_view str) const {
                return CodePointView<char16_t>(str);
            }

            inline auto operator()(std::u32string_view str) const {
                return CodePointView<char32_t>(str);
            }

            inline auto operator()(std::string_view str) const {
                // treat the std::string_view as UTF-8
                return CodePointView<char8_t>(std::u8string_view(reinterpret_cast<char8_t const*>(str.data()), str.size()));
            }

            auto operator()(std::wstring_view str) const requires (sizeof(wchar_t) == sizeof(char16_t)) {
                // treat the std::wstring_view as UTF-16
                return CodePointView<char16_t>(std::u16string_view(reinterpret_cast<const char16_t*>(str.data()), str.size()));
            }

            auto operator()(std::wstring_view str) const requires (sizeof(wchar_t) == sizeof(char32_t)) {
                // treat the std::wstring_view as UTF-32
                return CodePointView<char32_t>(std::u32string_view(reinterpret_cast<const char32_t*>(str.data()), str.size()));
            }
        };
        constexpr code_points_t code_points;

        /// @brief indicates whether the specified unicode code point is categorized as whitespace
        /// @see https://en.wikipedia.org/wiki/Template:Whitespace_%28Unicode%29
        bool is_whitespace(char16_t ch);

        /// @overload
        bool is_whitespace(char32_t codepoint);

        /// @brief drops the leading unicode whitespace from the unicode string view
        /// @param str the string view from which whitespace will be dropped
        /// @return str sans the leading whitespace
        std::u8string_view drop_leading_whitespace(std::u8string_view str);

        /// @overload
        std::u16string_view drop_leading_whitespace(std::u16string_view str);

        /// @overload
        std::u32string_view drop_leading_whitespace(std::u32string_view str);

        /// @brief drops the trailing unicode whitespace from the unicode string view
        /// @param str the string view from which whitespace will be dropped
        /// @return str sans the trailing whitespace
        std::u8string_view drop_trailing_whitespace(std::u8string_view str);

        /// @overload
        std::u16string_view drop_trailing_whitespace(std::u16string_view str);

        /// @overload
        std::u32string_view drop_trailing_whitespace(std::u32string_view str);

        /// @brief Validates whether a Unicode string view contains well-formed code points.
        /// 
        /// This function checks if the input string view contains valid UTF-encoded
        /// data for the given character type. It attempts to enumerate all code points
        /// using `unicode::code_points`, returning `true` if no decoding errors occur.
        /// 
        /// @param str The input string view to validate.
        /// @return `true` if the string is empty or contains only valid code points;
        ///         `false` if decoding fails due to malformed input.
        template <traits::character Char>
        bool is_valid_utf(std::basic_string_view<Char> str) noexcept {
            // trivial case
            if (str.empty()) {
                return true;
            }

            // iterate over the code points
            try {
                auto cps = unicode::code_points(str);
                while (!cps.empty()) {
                    cps.pop_front();
                };
                return true;
            }
            catch (...) {
                return false;
            }
        }

        /// @brief Encodes a single Unicode code point to a target buffer
        /// @details code_point_to_utf overloads are the conversion primitives
        /// to UTF-8, UTF-16, and UTF-32 encoding, used primarily for transcode.
        std::u8string_view code_point_to_utf(char32_t cp, std::span<char8_t> buffer);
        std::u16string_view code_point_to_utf(char32_t cp, std::span<char16_t> buffer);
        std::u32string_view code_point_to_utf(char32_t cp, std::span<char32_t> buffer);
        std::string_view code_point_to_utf(char32_t cp, std::span<char> buffer);
        std::wstring_view code_point_to_utf(char32_t cp, std::span<wchar_t> buffer);

        /// @brief Transcodes a Unicode string view from one character type to another.
        /// 
        /// Supports conversion between UTF-8, UTF-16, and UTF-32 encoding.
        /// 
        /// @tparam ToChar The target character type (e.g., `char8_t`, `char16_t`, `char32_t`).
        /// @tparam FromChar The source character type (must differ from `ToChar`).
        /// @param str The input Unicode string view to transcode.
        /// @return A string view of the transcoded result in the target character type.
        /// 
        /// @see unicode::code_points
        /// @see unicode::code_point_to_utf
        namespace implementation {
            template <traits::character ToChar, traits::character FromChar>
                requires (!std::same_as<ToChar, FromChar>) 
            std::basic_string<ToChar> transcode(std::basic_string_view<FromChar> str) {
                // trivial case
                if (str.empty()) {
                    return {};
                }

                constexpr size_t maxCharsPerCodePoint = sizeof(char32_t) / sizeof(ToChar);
                const size_t maxCodePoints = str.size();

                // reserve the maximum space needed, fill with 0
                std::basic_string<ToChar> result(maxCharsPerCodePoint * maxCodePoints, ToChar{0});
                std::span<ToChar> buffer(result.data(), result.size());

                // enumerate the code points in str, writing each to the target buffer
                for (auto cps = unicode::code_points(str); !cps.empty(); cps.pop_front()) {
                    auto consumed = unicode::code_point_to_utf(cps.front(), buffer);
                    buffer = buffer.subspan(consumed.size());
                }

                // shrink the result to just the consumed portion of the buffer
                result.resize(result.size() - buffer.size());
                return result;
            }

            template <traits::character ToChar, traits::character FromChar>
                requires (std::same_as<ToChar, FromChar>)
            std::basic_string<ToChar> transcode(std::basic_string_view<FromChar> str) {
                // no transcoding necessary, just return a copy
                return str;
            }
        }

        // these helpers are needed because the compiler will not perform an implicit conversion
        // to a templated std::basic_string_view<FromChar>.
        template <traits::character ToChar>
        std::basic_string<ToChar> transcode(std::basic_string_view<char> str) { 
            return implementation::transcode<ToChar>(str);
        }

        template <traits::character ToChar>
        std::basic_string<ToChar> transcode(std::basic_string_view<wchar_t> str) { 
            return implementation::transcode<ToChar>(str);
        }

        template <traits::character ToChar>
        std::basic_string<ToChar> transcode(std::basic_string_view<char8_t> str) { 
            return implementation::transcode<ToChar>(str);
        }

        template <traits::character ToChar>
        std::basic_string<ToChar> transcode(std::basic_string_view<char16_t> str) { 
            return implementation::transcode<ToChar>(str);
        }

        template <traits::character ToChar>
        std::basic_string<ToChar> transcode(std::basic_string_view<char32_t> str) { 
            return implementation::transcode<ToChar>(str);
        }

    } // namespace unicode

} // namespace dragon::strings
