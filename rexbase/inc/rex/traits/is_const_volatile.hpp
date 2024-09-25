#pragma once

#include "rex/traits/integral_constant.hpp"

namespace rex {

template <typename t> struct is_const                : false_type {};
template <typename t> struct is_const<const t>       : true_type  {};
template <typename t> struct is_volatile             : false_type {};
template <typename t> struct is_volatile<volatile t> : true_type  {};

/// @brief True if `t` is a constant type, else false. 
template <typename t> inline constexpr bool is_const_v = is_const<t>::value;
/// @brief True if `t` is a volatile type, else false. 
template <typename t> inline constexpr bool is_volatile_v = is_volatile<t>::value;

//

template <typename t> struct add_const    { using type = const t; };
template <typename t> struct add_volatile { using type = volatile t; };
template <typename t> struct add_cv       { using type = const volatile t; };

/// @brief An alias to a type that has const qualifier added to the type `t`.
template <typename t> using add_const_t = typename add_const<t>::type;
/// @brief An alias to a type that has volatile qualifier added to the type `t`.
template <typename t> using add_volatile_t = typename add_volatile<t>::type;
/// @brief An alias to a type that has const-volatile qualifier added to the type `t`.
template <typename t> using add_cv_t = typename add_cv<t>::type;

//

template <typename t> struct remove_const                { using type = t; };
template <typename t> struct remove_const<const t>       { using type = t; };
template <typename t> struct remove_volatile             { using type = t; };
template <typename t> struct remove_volatile<volatile t> { using type = t; };
template <typename t> struct remove_cv                   { using type = t; };
template <typename t> struct remove_cv<const t>          { using type = t; };
template <typename t> struct remove_cv<volatile t>       { using type = t; };
template <typename t> struct remove_cv<const volatile t> { using type = t; };

/// @brief An alias to a type that has const qualifier removed (if existed) from the type `t`.
template <typename t> using remove_const_t = typename remove_const<t>::type;
/// @brief An alias to a type that has volatile qualifier removed (if existed) from the type `t`.
template <typename t> using remove_volatile_t = typename remove_volatile<t>::type;
/// @brief An alias to a type that has const-volatile qualifier removed (if existed) from the type `t`.
template <typename t> using remove_cv_t = typename remove_cv<t>::type;

// Non-standard extra

template <typename t, typename u> struct match_cv                      { using type = remove_cv_t<u>;                };
template <typename t, typename u> struct match_cv<const t, u>          { using type = const remove_cv_t<u>;          };
template <typename t, typename u> struct match_cv<volatile t, u>       { using type = volatile remove_cv_t<u>;       };
template <typename t, typename u> struct match_cv<const volatile t, u> { using type = const volatile remove_cv_t<u>; };

/// @brief An alias to a type that has const-volatile qualifier added to `u` such that the qualifiers match `t`.
template <typename t, typename u> using match_cv_t = typename match_cv<t, u>::type; 

} // namespace rex