#pragma once

#include "rex/traits/integral_constant.hpp"

namespace rex {

template <typename t, typename u> struct is_base_of
    : bool_constant<__is_base_of(t, u)> {};

/// @brief True if `u` is same type or derived from `t`, else false.
template <typename t, typename u> inline constexpr bool is_base_of_v = is_base_of<t, u>::value;

} // namespace rex