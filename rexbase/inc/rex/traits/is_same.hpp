#pragma once

#include "rex/traits/integral_constant.hpp"

namespace rex {

template <typename t, typename u> struct is_same        : false_type {};
template <typename t>             struct is_same<t, t>  : true_type  {};

/// @brief True if type `t` is the same as type `u`, else false.
template <typename t, typename u> inline constexpr bool is_same_v = is_same<t, u>::value;

//

template <typename t, typename... u> struct is_any_same    : bool_constant<(is_same_v<t, u> || ...)> {};
template <typename t>                struct is_any_same<t> : false_type {};
template <typename t, typename... u> struct is_all_same    : bool_constant<(is_same_v<t, u> && ...)> {};
template <typename t>                struct is_all_same<t> : false_type {};

/// @brief True if `t` matches any of the types in `...u`, else false.
template <typename t, typename... u> inline constexpr bool is_any_same_v = is_any_same<t, u...>::value;
/// @brief True if `t` matches all of the types in `...u`, else false.
template <typename t, typename... u> inline constexpr bool is_all_same_v = is_all_same<t, u...>::value;

} // namespace rex