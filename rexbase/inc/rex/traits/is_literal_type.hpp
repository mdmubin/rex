#pragma once

#include "rex/traits/integral_constant.hpp"

namespace rex {

template <typename t> struct is_literal_type
    : bool_constant<__is_literal_type(t)> {};

/// @brief True if `t` is a literal type, else false.
template <typename t> inline constexpr bool is_literal_type_v = is_literal_type<t>::value;

} // namespace rex