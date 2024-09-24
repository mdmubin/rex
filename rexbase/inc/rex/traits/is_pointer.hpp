#pragma once

#include "rex/traits/integral_constant.hpp"

namespace rex {

template <typename t> struct is_pointer                    : false_type {};
template <typename t> struct is_pointer<t*>                : true_type  {};
template <typename t> struct is_pointer<t* const>          : true_type  {};
template <typename t> struct is_pointer<t* volatile>       : true_type  {};
template <typename t> struct is_pointer<t* const volatile> : true_type  {};

/// @brief True if `t` is a pointer, else false.
template <typename t> inline constexpr bool is_pointer_v = is_pointer<t>::value;

//

template <typename t> struct add_pointer      { using type = t*; };
template <typename t> struct add_pointer<t&>  { using type = t*; };
template <typename t> struct add_pointer<t&&> { using type = t*; };

/// @brief An alias to a type that has a pointer added to the type `t`.
/// @note If `t` is a reference, the pointer is added to the reference removed `t`.
template <typename t> using add_pointer_t = typename add_pointer<t>::type;

//

template <typename t> struct remove_pointer                    { using type = t; };
template <typename t> struct remove_pointer<t*>                { using type = t; };
template <typename t> struct remove_pointer<t* const>          { using type = t; };
template <typename t> struct remove_pointer<t* volatile>       { using type = t; };
template <typename t> struct remove_pointer<t* const volatile> { using type = t; };

/// @brief An alias to a type that has a pointer removed (if any existed) from the type `t`.
template <typename t> using remove_pointer_t = typename remove_pointer<t>::type;

} // namespace rex