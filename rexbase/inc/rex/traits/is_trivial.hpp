#pragma once

#include "rex/traits/integral_constant.hpp"

namespace rex {

template <typename t> struct is_trivial 
    : bool_constant<__is_trivial(t)> {};

template <typename t> struct is_trivially_copyable
    : bool_constant<__is_trivially_copyable(t)> {};

/// @brief True if `t` is a trivial type, else false.
template <typename t> inline constexpr bool is_trivial_v = is_trivial<t>::value;
/// @brief True if `t` may be trivially copied, else false.
template <typename t> inline constexpr bool is_trivially_copyable_v = is_trivially_copyable<t>::value;

} // namespace rex