#pragma once

#include "rex/types.hpp"
#include "rex/utils/declval.hpp"
#include "rex/traits/integral_constant.hpp"
#include "rex/traits/enable_if.hpp"
#include "rex/traits/is_reference.hpp"
#include "rex/traits/is_constructible.hpp"
#include "rex/traits/is_assignable.hpp"

namespace rex::impl {

template <typename t, typename u> struct swappable_with;
template <typename t, typename u> struct nothrow_swappable_with;

// HELPERS

template <typename t,
    bool is_enabled = is_move_constructible_v<t> && is_move_assignable_v<t>,
    bool is_nothrow = is_nothrow_move_constructible_v<t> && is_nothrow_move_assignable_v<t>
> enable_if_t<is_enabled> swap_decl(t&, t&) noexcept(is_nothrow);

template <typename t, usz l,
    bool is_enabled = swappable_with<t&, t&>::value,
    bool is_nothrow = nothrow_swappable_with<t&, t&>::value
> enable_if_t<is_enabled> swap_decl(t (&)[l], t (&)[l]) noexcept(is_nothrow);

// IMPL

template <typename t, typename u>
struct swappable_with
{
    template <typename a, typename b, typename = decltype(swap_decl(declval<a>(), declval<b>()))>
    static true_type check_swap(int);
    template <typename, typename>
    static false_type check_swap(...);

    static constexpr bool value = decltype(check_swap<t, u>(0))::value && decltype(check_swap<u, t>(0))::value;
};

template <typename t, typename u>
struct nothrow_swappable_with
{
    template <typename a, typename b, bool is_nothrow = noexcept(swap(declval<a>(), declval<b>()))>
    static bool_constant<is_nothrow> check_swap(int);
    template <typename>
    static false_type check_swap(...);

    static constexpr bool value = decltype(check_swap<t, u>(0))::value && decltype(check_swap<u, t>(0))::value;
};

} // namespace rex::impl

namespace rex {

template <typename t, typename u> struct is_swappable_with
    : bool_constant<impl::swappable_with<t, u>::value> {};
template <typename t, typename u> struct is_nothrow_swappable_with
    : bool_constant<impl::nothrow_swappable_with<t, u>::value> {};
template <typename t> struct is_swappable
    : is_swappable_with<add_lvalue_reference_t<t>, add_lvalue_reference_t<t>>{};
template <typename t> struct is_nothrow_swappable
    : is_nothrow_swappable_with<add_lvalue_reference_t<t>, add_lvalue_reference_t<t>> {};

//

/// @brief True if `t` may be swapped with `u`, else false.
template <typename t, typename u> inline constexpr bool is_swappable_with_v = is_swappable_with<t, u>::value;
/// @brief True if `t` may be swapped with `u` without throwing an exception, else false.
template <typename t, typename u> inline constexpr bool is_nothrow_swappable_with_v = is_nothrow_swappable_with<t, u>::value;

/// @brief True if two `t` may be swapped with each other, else false.
template <typename t> inline constexpr bool is_swappable_v = is_swappable<t>::value;
/// @brief True if two `t` may be swapped with each other without throwing an exception, else false.
template <typename t> inline constexpr bool is_nothrow_swappable_v = is_nothrow_swappable<t>::value;

} // namespace rex