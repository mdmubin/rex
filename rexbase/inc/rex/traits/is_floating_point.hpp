#pragma once

#include "rex/traits/integral_constant.hpp"
#include "rex/traits/is_same.hpp"
#include "rex/traits/is_const_volatile.hpp"

namespace rex {

template <typename t> struct is_floating_point
    : bool_constant<is_any_same_v
    <
        remove_cv_t<t>,
        // check if any of the types below is same as t with const volatile removed
        float, double, long double
    >> {};

/// @brief True if `t` is floating point type, else false. 
template <typename t> inline constexpr bool is_floating_point_v = is_floating_point<t>::value;

} // namespace rex