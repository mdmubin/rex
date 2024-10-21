#pragma once

#include "rex/traits/integral_constant.hpp"

namespace rex {

template <typename t> struct negation 
    : bool_constant<!static_cast<bool>(t::value)> {};

/// @brief Negates the integer value of `t`.
/// @note `t` is expected to be an `integral_constant` type.
template <typename t> inline constexpr bool negation_v = negation<t>::value;

} // namespace rex