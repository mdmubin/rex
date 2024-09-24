#pragma once

#include "rex/traits/integral_constant.hpp"

namespace rex {

template <typename t> struct is_abstract
    : bool_constant<__is_abstract(t)> {};

/// @brief True if `t` is an abstract type, else false.
template <typename t> inline constexpr bool is_abstract_v = is_abstract<t>::value;

} // namespace rex