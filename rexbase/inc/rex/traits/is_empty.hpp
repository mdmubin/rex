#pragma once

#include "rex/traits/integral_constant.hpp"

namespace rex
{

template <typename t> struct is_empty
    : bool_constant<__is_empty(t)> {};

/// @brief True if `t` is an empty type, else false. 
template <typename t> inline constexpr bool is_empty_v = is_empty<t>::value;

} // namespace name