#pragma once

#include "rex/types.hpp"
#include "rex/traits/integral_constant.hpp"

namespace rex {

template <typename t>        struct is_array       : false_type {};
template <typename t>        struct is_array<t[]>  : true_type  {};
template <typename t, usz l> struct is_array<t[l]> : true_type  {};

/// @brief True if `t` is an array type, else false. 
template <typename t> inline constexpr bool is_array_v = is_array<t>::value;

} // namespace rex