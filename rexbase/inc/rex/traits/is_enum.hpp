#pragma once

#include "rex/traits/integral_constant.hpp"

namespace rex {

template <typename t> struct is_enum
    : bool_constant<__is_enum(t)> {};

/// @brief True if `t` is an enum type, else false.
template <typename t> inline constexpr bool is_enum_v = is_enum<t>::value;

} // namespace rex