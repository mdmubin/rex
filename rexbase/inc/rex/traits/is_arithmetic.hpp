#pragma once

#include "rex/traits/integral_constant.hpp"
#include "rex/traits/is_integral.hpp"
#include "rex/traits/is_floating_point.hpp"

namespace rex {

template <typename t> struct is_arithmetic
    : bool_constant<is_integral_v<t> || is_floating_point_v<t>> {};

/// @brief True if `t` is arithmetic type, else false.
template <typename t> inline constexpr bool is_arithmetic_v = is_arithmetic<t>::value;

} // namespace rex