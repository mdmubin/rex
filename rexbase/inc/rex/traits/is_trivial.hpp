#pragma once

#include "rex/traits/integral_constant.hpp"

namespace rex {

template <typename t> struct is_trivial 
    : bool_constant<__is_trivial(t)> {};

/// @brief True if `t` is a trivial type, else false.
template <typename t>
inline constexpr bool is_trivial_v = is_trivial<t>::value;

} // namespace rex