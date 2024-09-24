#pragma once

#include "rex/traits/integral_constant.hpp"

namespace rex {

template <typename t> struct is_lvalue_reference      : false_type {};
template <typename t> struct is_lvalue_reference<t&>  : true_type  {};
template <typename t> struct is_rvalue_reference      : false_type {};
template <typename t> struct is_rvalue_reference<t&&> : true_type  {};
template <typename t> struct is_reference             : false_type {};
template <typename t> struct is_reference<t&>         : true_type  {};
template <typename t> struct is_reference<t&&>        : true_type  {};

/// @brief True if `t` is an lvalue reference, else false.
template <typename t> inline constexpr bool is_lvalue_reference_v = is_lvalue_reference<t>::value;
/// @brief True if `t` is an rvalue reference, else false.
template <typename t> inline constexpr bool is_rvalue_reference_v = is_rvalue_reference<t>::value;
/// @brief True if `t` is either an lvalue or an rvalue reference, else false.
template <typename t> inline constexpr bool is_reference_v = is_reference<t>::value;

//

template <typename t> struct remove_lvalue_reference      { using type = t; };
template <typename t> struct remove_lvalue_reference<t&>  { using type = t; };
template <typename t> struct remove_rvalue_reference      { using type = t; };
template <typename t> struct remove_rvalue_reference<t&&> { using type = t; };
template <typename t> struct remove_reference             { using type = t; };
template <typename t> struct remove_reference<t&>         { using type = t; };
template <typename t> struct remove_reference<t&&>        { using type = t; };

/// @brief An alias to a type that has lvalue reference removed (if existed) from the type `t`. 
template <typename t> using remove_lvalue_reference_t = typename remove_lvalue_reference<t>::type;
/// @brief An alias to a type that has rvalue reference removed (if existed) from the type `t`. 
template <typename t> using remove_rvalue_reference_t = typename remove_rvalue_reference<t>::type;
/// @brief An alias to a type that has all references removed (if any existed) from the type `t`.
template <typename t> using remove_reference_t = typename remove_reference<t>::type;

//

template <typename t> struct add_lvalue_reference       { using type = t&;   };
template <>           struct add_lvalue_reference<void> { using type = void; };
template <typename t> struct add_rvalue_reference       { using type = t&&;  };
template <>           struct add_rvalue_reference<void> { using type = void; };

/// @brief An alias to a type that has lvalue reference added (if not existed) to the type `t`.
/// @note No lvalue reference can exist for void type, so it aliases itself (void).
template <typename t> using add_lvalue_reference_t = typename add_lvalue_reference<t>::type;
/// @brief An alias to a type that has rvalue reference added (if not existed) to the type `t`.
/// @note No rvalue reference can exist for void type, so it aliases itself (void).
template <typename t> using add_rvalue_reference_t = typename add_rvalue_reference<t>::type;

} // namespace rex