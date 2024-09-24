#pragma once

#include "rex/traits/integral_constant.hpp"

namespace rex {

template <typename t> struct is_aggregate
    : bool_constant<__is_aggregate(t)> {};

/// @brief True if `t` is an aggregate type, else false.
template <typename t> inline constexpr bool is_aggregate_v = is_aggregate<t>::value;

} // namespace rex