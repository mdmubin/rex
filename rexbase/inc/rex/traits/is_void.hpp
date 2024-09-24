#pragma once

#include "rex/traits/integral_constant.hpp"
#include "rex/traits/is_same.hpp"
#include "rex/traits/is_const_volatile.hpp"

namespace rex {

/// @brief Utility type alias that maps any type to void.
template <typename...> using void_t = void;

template <typename t> struct is_void
    : bool_constant <is_same_v<remove_cv_t<t>, void>> {};

/// @brief True if `t` is void, else false. 
template <typename t> inline constexpr bool is_void_v = is_void<t>::value;

} // namespace rex