#pragma once

#include "rex/traits/integral_constant.hpp"
#include "rex/traits/is_fundamental.hpp"

namespace rex {

template <typename t> struct is_compound
    : bool_constant<!is_fundamental_v<t>> {};

/// @brief True if `t` is a compound type (not a fundamental type), else false.
template <typename t> inline constexpr bool is_compound_v = is_compound<t>::value;

} // namespace rex