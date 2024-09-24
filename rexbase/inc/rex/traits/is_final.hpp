#pragma once

#include "rex/traits/integral_constant.hpp"

namespace rex {

template <typename t> struct is_final
    : bool_constant<__is_final(t)> {};

/// @brief True if `t` is a final class, else false.
template <typename t> inline constexpr bool is_final_v = is_final<t>::value;

} // namespace rex