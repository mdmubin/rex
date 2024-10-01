#pragma once

#include "rex/traits/integral_constant.hpp"
#include "rex/traits/is_const_volatile.hpp"
#include "rex/traits/is_reference.hpp"

namespace rex {

template <typename t> struct is_function
    : bool_constant<!is_const_v<const t> && !is_reference_v<t>> {};

/// @brief True if `t` if a function type, else false.
template <typename t> inline constexpr bool is_function_v = is_function<t>::value;

} // namespace rex