#pragma once

#include "rex/traits/integral_constant.hpp"

namespace rex {

template <typename t> struct is_standard_layout
    : bool_constant<__is_standard_layout(t)> {};

/// @brief True if `t` has a standard layout, else false.
template <typename t> inline constexpr bool is_standard_layout_v = is_standard_layout<t>::value;

} // namespace rex