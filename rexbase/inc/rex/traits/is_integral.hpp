#pragma once

#include "rex/traits/integral_constant.hpp"
#include "rex/traits/is_const_volatile.hpp"
#include "rex/traits/is_same.hpp"

namespace rex {

template <typename t> struct is_integral
    : bool_constant<is_any_same_v
    <
        remove_cv_t<t>,
        // check if any of the types below is same as t with const volatile removed
                 char,          short,          int,          long,          long long,
        unsigned char, unsigned short, unsigned int, unsigned long, unsigned long long,
          signed char,           bool,      wchar_t,      char16_t,           char32_t
    >> {};

/// @brief True if `t` is integer type, else false. 
template <typename t> inline constexpr bool is_integral_v = is_integral<t>::value;

} // namespace rex