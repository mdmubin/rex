#pragma once

#include "rex/traits/integral_constant.hpp"

namespace rex {

template <typename...>              struct conjunction          : true_type {};
template <typename t>               struct conjunction<t>       : bool_constant<static_cast<bool>(t::value)> {};
template <typename t, typename...u> struct conjunction<t, u...> : bool_constant<static_cast<bool>(t::value) && conjunction<u...>::value> {};

/// @brief True if all types in `...t` is equivalent to `true_type`, else false.
/// @note Value of empty `...t` is true.
template <typename ...t> inline constexpr bool conjunction_v = conjunction<t...>::value;

} // namespace rex