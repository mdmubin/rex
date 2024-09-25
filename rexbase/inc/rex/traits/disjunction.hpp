#pragma once

#include "rex/traits/integral_constant.hpp"

namespace rex {

template <typename...> struct disjunction
    : false_type {};
template <typename t> struct disjunction<t>
    : bool_constant<bool(t::value)> {};
template <typename t, typename...u> struct disjunction<t, u...>
    : bool_constant<bool(t::value) || disjunction<u...>::value> {};

/// @brief True if any type in `...t` is equivalent to `true_type`, else false.
/// @note Value of empty `...t` is false.
template <typename ...t> inline constexpr bool disjunction_v = disjunction<t...>::value;

} // namespace rex