/// @file dragon/traits.h
/// @brief Provides type traits and concepts for compile-time type introspection and validation.
/// @namespace dragon::traits
/// @details This header defines a collection of C++23 concepts and type traits for checking properties
///          such as array types, numeric types, signedness, enum classes, and standard integral or
///          character types. It also includes a debug build indicator for conditional compilation.
#pragma once

#include <dragon/platform_dependencies.h>

#include <concepts>
#include <optional>
#include <type_traits>
#include <limits>

namespace dragon::traits
{
    /// @brief Concept to check if a type T is one of the specified types.
    /// @tparam T The type to check.
    /// @tparam Types Variadic list of types to compare against.
    /// @details Evaluates to `true` if T is exactly one of the types in Types, using std::same_as.
    /// @example
    ///   static_assert(any_of<int, int, float, double>); // true
    ///   static_assert(any_of<int, float, double>);     // false
    template <typename T, typename... Types>
    concept any_of = (std::same_as<T, Types> || ...);

    /// @brief Concept to check if a type is an array with a specific element type.
    /// @tparam T The type to check.
    /// @tparam E The expected element type of the array.
    /// @details Evaluates to `true` if T is an array type (std::is_array_v<T>) and its element type,
    ///          after removing const/volatile qualifiers, is the same as E.
    /// @example
    ///   static_assert(array_of<int[5], int>);        // true
    ///   static_assert(array_of<const int[3], int>);  // true
    ///   static_assert(array_of<int*, int>);          // false
    ///   static_assert(array_of<int[5], double>);     // false
    template <typename T, typename E>
    concept array_of = std::is_array_v<T> && std::same_as<std::remove_cv_t<std::remove_extent_t<T>>, E>;

    /// @brief Concept to check if a type is an array with an element type matching any of the specified types.
    /// @tparam T The type to check.
    /// @tparam Types Variadic list of types to compare the array's element type against.
    /// @details Evaluates to `true` if T is an array type and its element type (after removing const/volatile
    ///          qualifiers) is the same as any of the types in Types, using the array_of concept.
    /// @example
    ///   static_assert(array_of_any_of<int[5], int, double, char>);        // true
    ///   static_assert(array_of_any_of<double[3], int, double, char>);    // true
    ///   static_assert(array_of_any_of<const int[2], int, double>);       // true
    ///   static_assert(array_of_any_of<std::string[2], int, double>);     // false
    template <typename T, typename... Types>
    concept array_of_any_of = (array_of<T, Types> || ...);

    /// @brief Concept to check if a type is a character type.
    /// @tparam T The type to check.
    /// @details Evaluates to `true` if T is one of the character types:
    ///          signed char, unsigned char, char, wchar_t, char8_t, char16_t, char32_t.
    /// @example
    ///   static_assert(character<char>);     // true
    ///   static_assert(character<char16_t>); // true
    ///   static_assert(character<int>);      // false
    template <typename T>
    concept character = any_of<T, signed char, unsigned char, char, wchar_t, char8_t, char16_t, char32_t>;

    /// @brief Concept to check if a type T is convertible to any of the specified types.
    /// @tparam T The type to check for convertibility.
    /// @tparam Types Variadic list of types to check convertibility against.
    /// @details Evaluates to `true` if T can be implicitly converted to at least one of the types in Types.
    /// @example
    ///   static_assert(convertible_to_any_of<int, float, double, long>); // true
    ///   static_assert(convertible_to_any_of<std::string, int, float>);  // false
    template <typename T, typename... Types>
    concept convertible_to_any_of = (std::convertible_to<T, Types> || ...);

    /// @brief Concept to check if two integral types have different signedness.
    /// @tparam T First integral type.
    /// @tparam U Second integral type.
    /// @details Evaluates to `true` if both T and U are integral types and have different signedness
    ///          (one signed, one unsigned).
    /// @example
    ///   static_assert(different_signedness<int, unsigned>); // true
    ///   static_assert(different_signedness<int, long>);     // false
    template <typename T, typename U>
    concept different_signedness = std::integral<T> && std::integral<U> && (std::is_signed_v<T> != std::is_signed_v<U>);

    /// @brief Concept to check if a type has a valid std::numeric_limits specialization.
    /// @tparam T The type to check.
    /// @details Evaluates to `true` if std::numeric_limits<T> is specialized (is_specialized is true)
    ///          and provides min() and max() functions returning the same type T.
    /// @example
    ///   static_assert(has_numeric_limits<int>);    // true
    ///   static_assert(has_numeric_limits<std::string>); // false
    template <typename T>
    concept has_numeric_limits = requires() {
        requires std::numeric_limits<T>::is_specialized;
        { std::numeric_limits<T>::min() } -> std::same_as<T>;
        { std::numeric_limits<T>::max() } -> std::same_as<T>;
    };

    /// @brief Concept to check if a type is an enum class.
    /// @tparam T The type to check.
    /// @details Evaluates to `true` if T is an enumeration type (std::is_enum_v<T>) and is not
    ///          implicitly convertible to int, ensuring it is a scoped enum (enum class).
    /// @example
    ///   enum class Color { Red, Blue }; static_assert(is_enum_class<Color>); // true
    ///   enum Unscoped { A, B }; static_assert(is_enum_class<Unscoped>);       // false
    template <typename T>
    concept is_enum_class = std::is_enum_v<T> && !std::is_convertible_v<T, int>;

    /// @brief Concept to check if a type is numeric (floating-point or integral).
    /// @tparam T The type to check.
    /// @details Evaluates to `true` if T is either a floating-point or integral type, as defined by
    ///          std::floating_point or std::integral.
    /// @example
    ///   static_assert(numeric<int>);    // true
    ///   static_assert(numeric<double>); // true
    ///   static_assert(numeric<std::string>); // false
    template <typename T>
    concept numeric = std::floating_point<T> || std::integral<T>;

    /// @brief Concept to check if two integral types have the same signedness.
    /// @tparam T First integral type.
    /// @tparam U Second integral type.
    /// @details Evaluates to `true` if both T and U are integral types and have the same signedness
    ///          (both signed or both unsigned).
    /// @example
    ///   static_assert(same_signedness<int, long>);         // true (both signed)
    ///   static_assert(same_signedness<unsigned, int>);     // false
    template <typename T, typename U>
    concept same_signedness = std::integral<T> && std::integral<U> && (std::is_signed_v<T> == std::is_signed_v<U>);

    /// @brief Concept to check if a type is a standard integral type.
    /// @tparam T The type to check.
    /// @details Evaluates to `true` if T is one of the standard integral types:
    ///          signed char, short, int, long, long long, or their unsigned counterparts.
    /// @example
    ///   static_assert(standard_integral<int>);          // true
    ///   static_assert(standard_integral<std::int32_t>); // false
    template <typename T>
    concept standard_integral = any_of<T, 
        signed char, short, int, long, long long,
        unsigned char, unsigned short, unsigned int, unsigned long, unsigned long long>;

}
