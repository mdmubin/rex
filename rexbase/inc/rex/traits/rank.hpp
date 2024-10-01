#pragma once

#include "rex/types.hpp"
#include "rex/traits/integral_constant.hpp"

namespace rex {

template <typename t>        struct rank       : integral_constant<usz, 0> {};
template <typename t>        struct rank<t[]>  : integral_constant<usz, rank<t>::value + 1> {};
template <typename t, usz l> struct rank<t[l]> : integral_constant<usz, rank<t>::value + 1> {};

/// @brief The number of dimensions of type `t`.
template <typename t> inline constexpr usz rank_v = rank<t>::value;

} // namespace rex