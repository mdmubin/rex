#pragma once

#include "rex/traits/integral_constant.hpp"
#include "rex/utils/declval.hpp"

namespace rex::impl {

// HELPER

template <typename t, typename u>
struct convertible_helper
{
    template <typename a> static void check(a);

    template <typename a, typename b, typename = decltype(check<b>(declval<a>()))>
    static true_type convertible(int);

    template <typename, typename>
    static false_type convertible(...);

    static constexpr bool value = (is_void_v<t> && is_void_v<u>) || decltype(convertible<t, u>(0))::value;
};

// IMPL

template <typename t, typename u>
struct is_convertible
    : bool_constant<convertible_helper<t, u>::value> {};

} // namespace rex::impl

namespace rex {

template <typename t, typename u> struct is_convertible : impl::is_convertible<t, u> {};

/// @brief True if `t` may be convertible to `u`, else false.
template <typename t, typename u> inline constexpr bool is_convertible_v = is_convertible<t, u>::value;

} // namespace rex