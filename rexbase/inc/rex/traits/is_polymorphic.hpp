#pragma once

#include "rex/traits/integral_constant.hpp"

namespace rex {

template<class t> struct is_polymorphic
    : bool_constant<__is_polymorphic(t)> {};

/// @brief True if `t` is a polymorphic type, else false.
template <typename t> inline constexpr bool is_polymorphic_v = is_polymorphic<t>::value;

} // namespace rex