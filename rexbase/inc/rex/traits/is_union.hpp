#pragma once

#include "rex/traits/integral_constant.hpp"

namespace rex {

template <typename t> struct is_union : bool_constant<__is_union(t)> {};

/// @brief True if `t` is a union type, else false. 
template <typename t> inline constexpr bool is_union_v = is_union<t>::value;

} // namespace rex