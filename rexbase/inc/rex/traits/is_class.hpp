#pragma once

#include "rex/traits/integral_constant.hpp"

namespace rex {

template <typename t> struct is_class
    : bool_constant<__is_class(t)> {};

/// @brief True if `t` is a class type, else false.
template <typename t> inline constexpr bool is_class_v = is_class<t>::value;

} // namespace rex