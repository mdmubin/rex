#pragma once

#include "rex/traits/integral_constant.hpp"
#include "rex/traits/is_reference.hpp"

namespace rex {

template <typename t, typename u> struct is_assignable
    : bool_constant<__is_assignable(t, u)> {};
template <typename t, typename u> struct is_trivially_assignable
    : bool_constant<__is_trivially_assignable(t, u)> {};
template <typename t, typename u> struct is_nothrow_assignable
    : bool_constant<__is_nothrow_assignable(t, u)> {};

/// @brief True if `u` maybe assigned to `t`, else false. 
template <typename t, typename u> inline constexpr bool is_assignable_v = is_assignable<t, u>::value;
/// @brief True if `u` maybe trivially assigned to `t`, else false.
template <typename t, typename u> inline constexpr bool is_trivially_assignable_v = is_trivially_assignable<t, u>::value;
/// @brief True if `u` maybe nothrow assigned to `t`, else false.
template <typename t, typename u> inline constexpr bool is_nothrow_assignable_v = is_nothrow_assignable<t, u>::value;

//

template <typename t> struct is_copy_assignable 
    : bool_constant<is_assignable_v<t, add_lvalue_reference_t<const t>>> {};
template <typename t> struct is_trivially_copy_assignable 
    : bool_constant<is_trivially_assignable_v<t, add_lvalue_reference_t<const t>>> {};
template <typename t> struct is_nothrow_copy_assignable 
    : bool_constant<is_nothrow_assignable_v<t, add_lvalue_reference_t<const t>>> {};

/// @brief True if `t` may be copy assigned, else false. 
template <typename t> inline constexpr bool is_copy_assignable_v = is_copy_assignable<t>::value;
/// @brief True if `t` may be trivially copy assigned, else false. 
template <typename t> inline constexpr bool is_trivially_copy_assignable_v = is_trivially_copy_assignable<t>::value;
/// @brief True if `t` may be nothrow copy assigned, else false. 
template <typename t> inline constexpr bool is_nothrow_copy_assignable_v = is_nothrow_copy_assignable<t>::value;

//

template <typename t> struct is_move_assignable 
    : bool_constant<is_assignable_v<t, add_rvalue_reference_t<t>>> {};
template <typename t> struct is_trivially_move_assignable 
    : bool_constant<is_trivially_assignable_v<t, add_rvalue_reference_t<t>>> {};
template <typename t> struct is_nothrow_move_assignable 
    : bool_constant<is_nothrow_assignable_v<t, add_rvalue_reference_t<t>>> {};

/// @brief True if `t` may be move assigned, else false. 
template <typename t> inline constexpr bool is_move_assignable_v = is_move_assignable<t>::value;
/// @brief True if `t` may be trivially move assigned, else false.
template <typename t> inline constexpr bool is_trivially_move_assignable_v = is_trivially_move_assignable<t>::value;
/// @brief True if `t` may be nothrow move assigned, else false.
template <typename t> inline constexpr bool is_nothrow_move_assignable_v = is_nothrow_move_assignable<t>::value;

} // namespace rex