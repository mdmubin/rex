#pragma once

#include "rex/traits/integral_constant.hpp"

namespace rex {

template <typename t> struct is_pod
    : bool_constant<__is_pod(t)> {};

/// @brief True if `t` is a plain-old data (pod) type, else false.
template <typename t> inline constexpr bool is_pod_v = is_pod<t>::value;

} // namespace rex