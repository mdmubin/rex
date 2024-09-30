#pragma once

#include "rex/traits/integral_constant.hpp"
#include "rex/traits/invoke_result.hpp"
#include "rex/traits/is_same.hpp"
#include "rex/traits/is_void.hpp"

namespace rex::impl {

template <typename, typename, typename...> struct is_invocable : false_type {};
template <typename f, typename... a>
struct is_invocable<void_t<decltype(invoke(declval<f>(), declval<a>()...))>, f, a...>
    : true_type {};

template <typename, typename, typename...> struct is_nt_invocable : false_type {};
template <typename f, typename... a>
struct is_nt_invocable<void_t<decltype(invoke(declval<f>(), declval<a>()...))>, f, a...>
    : bool_constant<noexcept(invoke(declval<f>(), declval<a>()...))> {};

template <typename, typename, typename, typename...> struct is_invocable_r : false_type {};
template <typename r, typename f, typename... a>
struct is_invocable_r<void_t<decltype(invoke(declval<f>(), declval<a>()...))>, r, f, a...>
    : bool_constant<is_same_v<r, decltype(invoke(declval<f>(), declval<a>()...))>> {};

template <typename, typename, typename, typename...> struct is_nt_invocable_r : false_type {};
template <typename r, typename f, typename... a>
struct is_nt_invocable_r<void_t<decltype(invoke(declval<f>(), declval<a>()...))>, r, f, a...>
    : bool_constant<is_same_v<r, decltype(invoke(declval<f>(), declval<a>()...))> && noexcept(invoke(declval<f>(), declval<a>()...))> {};

} // namespace rex::impl

namespace rex {

template <typename f, typename... a> struct is_invocable         : impl::is_invocable   <void, f, a...> {};
template <typename f, typename... a> struct is_nothrow_invocable : impl::is_nt_invocable<void, f, a...> {};

template <typename r, typename f, typename... a> struct is_invocable_r         : impl::is_invocable_r   <void, r, f, a...> {};
template <typename r, typename f, typename... a> struct is_nothrow_invocable_r : impl::is_nt_invocable_r<void, r, f, a...> {};

/// @brief True if `t` can be invoked using the args `...u`, else false.
template <typename t, typename... u> inline constexpr bool is_invocable_v = is_invocable<t, u...>::value;
/// @brief True if `t` can be invoked without throwing an exception using the args `...u`, else false.
template <typename t, typename... u> inline constexpr bool is_nothrow_invocable_v = is_nothrow_invocable<t, u...>::value;

/// @brief True if `t` can be invoked using the args `...u` to produce a return type that can be cast to `r`, else false.
template <typename r, typename t, typename... u> inline constexpr bool is_invocable_r_v = is_invocable_r<r, t, u...>::value;
/// @brief True if `t` can be invoked without throwing an exception using the args `...u` to produce a return type that can be cast to `r`, else false.
template <typename r, typename t, typename... u> inline constexpr bool is_nothrow_invocable_r_v = is_nothrow_invocable_r<r, t, u...>::value;

} // namespace rex