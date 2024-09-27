#pragma once

#include "rex/traits/integral_constant.hpp"
#include "rex/traits/is_reference.hpp"

namespace rex {

template <typename t, typename... u> struct is_constructible
    : bool_constant<__is_constructible(t, u...)> {};
template <typename t, typename... u> struct is_trivially_constructible
    : bool_constant<__is_trivially_constructible(t, u...)> {};
template <typename t, typename... u> struct is_nothrow_constructible
    : bool_constant<__is_nothrow_constructible(t, u...)> {};

/// @brief True if `t` can be constructed with the arguments `...u`, else false.
template <typename t, typename... u>inline constexpr bool is_constructible_v = is_constructible<t, u...>::value;
/// @brief True if `t` can be trivially constructed with the arguments `...u`, else false.
template <typename t, typename... u> inline constexpr bool is_trivially_constructible_v = is_trivially_constructible<t, u...>::value;
/// @brief True if `t` can be nothrow constructed with the arguments `...u`, else false.
template <typename t, typename... u> inline constexpr bool is_nothrow_constructible_v = is_nothrow_constructible<t, u...>::value;

//

template <typename t> struct is_default_constructible
    : bool_constant<is_constructible_v<t>> {};
template <typename t> struct is_trivially_default_constructible
    : bool_constant<is_trivially_constructible_v<t>> {};
template <typename t> struct is_nothrow_default_constructible
    : bool_constant<is_nothrow_constructible_v<t>> {};

/// @brief True if `t` can be default constructed, else false.
template <typename t> inline constexpr bool is_default_constructible_v = is_default_constructible<t>::value;
/// @brief True if `t` can be trivially default constructed, else false.
template <typename t> inline constexpr bool is_trivially_default_constructible_v = is_trivially_default_constructible<t>::value;
/// @brief True if `t` can be nothrow default constructed, else false.
template <typename t> inline constexpr bool is_nothrow_default_constructible_v = is_nothrow_default_constructible<t>::value;

//

template <typename t> struct is_copy_constructible
    : bool_constant<is_constructible_v<t, add_lvalue_reference_t<const t>>> {};
template <typename t> struct is_trivially_copy_constructible
    : bool_constant<is_trivially_constructible_v<t, add_lvalue_reference_t<const t>>> {};
template <typename t> struct is_nothrow_copy_constructible
    : bool_constant<is_nothrow_constructible_v<t, add_lvalue_reference_t<const t>>> {};

/// @brief True if `t` can be copy constructed, else false.
template <typename t> inline constexpr bool is_copy_constructible_v = is_copy_constructible<t>::value;
/// @brief True if `t` can be trivially copy constructed, else false.
template <typename t> inline constexpr bool is_trivially_copy_constructible_v = is_trivially_copy_constructible<t>::value;
/// @brief True if `t` can be nothrow copy constructed, else false.
template <typename t> inline constexpr bool is_nothrow_copy_constructible_v = is_nothrow_copy_constructible<t>::value;

//

template <typename t> struct is_move_constructible
    : bool_constant<is_constructible_v<t, add_rvalue_reference_t<t>>> {};
template <typename t> struct is_trivially_move_constructible
    : bool_constant<is_trivially_constructible_v<t, add_rvalue_reference_t<t>>> {};
template <typename t> struct is_nothrow_move_constructible
    : bool_constant<is_nothrow_constructible_v<t, add_rvalue_reference_t<t>>> {};

/// @brief True if `t` can be move constructed, else false.
template <typename t> inline constexpr bool is_move_constructible_v = is_move_constructible<t>::value;
/// @brief True if `t` can be trivially move constructed, else false.
template <typename t> inline constexpr bool is_trivially_move_constructible_v = is_trivially_move_constructible<t>::value;
/// @brief True if `t` can be nothrow move constructed, else false.
template <typename t> inline constexpr bool is_nothrow_move_constructible_v = is_nothrow_move_constructible<t>::value;

} // namespace rex