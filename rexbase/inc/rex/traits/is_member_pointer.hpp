#pragma once

#include "rex/traits/integral_constant.hpp"
#include "rex/traits/is_const_volatile.hpp"
#include "rex/traits/is_function.hpp"

namespace rex::impl {

template <typename t>             inline constexpr bool member_ptr            = false;
template <typename t, typename u> inline constexpr bool member_ptr<t u::*>    = true;
template <typename t>             inline constexpr bool member_fn_ptr         = false;
template <typename t, typename u> inline constexpr bool member_fn_ptr<t u::*> = is_function_v<t>;
template <typename t>             inline constexpr bool member_obj_ptr        = member_ptr<t> && !member_fn_ptr<t>;

} // namespace rex::impl

namespace rex {

template <typename t> struct is_member_pointer
    : bool_constant<impl::member_ptr<remove_cv_t<t>>> {};

template <typename t> struct is_member_function_pointer
    : bool_constant<impl::member_fn_ptr<remove_cv_t<t>>> {};

template <typename t> struct is_member_object_pointer
    : bool_constant<impl::member_obj_ptr<remove_cv_t<t>>> {};

//

/// @brief True if `t` is a pointer to a non-static class member, else false. 
template <typename t> inline constexpr bool is_member_pointer_v = is_member_pointer<t>::value;
/// @brief True if `t` is a pointer to non-static a class member function, else false. 
template <typename t> inline constexpr bool is_member_function_pointer_v = is_member_function_pointer<t>::value;
/// @brief True if `t` is a pointer to a non-static class member object, else false. 
template <typename t> inline constexpr bool is_member_object_pointer_v = is_member_object_pointer<t>::value;

} // namespace rex