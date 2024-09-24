#pragma once

#include "rex/traits/integral_constant.hpp"
#include "rex/traits/is_arithmetic.hpp"
#include "rex/traits/is_null_pointer.hpp"
#include "rex/traits/is_void.hpp"

namespace rex {

template <typename t> struct is_fundamental
    : bool_constant<is_arithmetic_v<t> || is_null_pointer_v<t> || is_void_v<t>> {};

/// @brief True if `t` is a fundamental type, else false. 
template <typename t> inline constexpr bool is_fundamental_v = is_fundamental<t>::value;

} // namespace rex