#pragma once

#include "rex/config.hpp"
#include "rex/traits/extent.hpp"
#include "rex/traits/is_function.hpp"
#include "rex/types.hpp"
#include "rex/utils/declval.hpp"

namespace rex::impl {

/* IS_DESTRUCTIBLE HELPERS */

template <typename t, bool = is_function_v<t>>
struct destructible_helper
{
    static constexpr bool value = false;
};
template <typename t>
struct destructible_helper<t, false>
{
    template <typename u, typename v = decltype(declval<u &>().~u())>
    static true_type  check(int);
    template <typename>
    static false_type check(...);

    static constexpr bool value = decltype(check<remove_all_extents_t<t>>(0))::value;
};

/* IS_DESTRUCTIBLE IMPL */

template <typename t> struct is_destructible       :  bool_constant<destructible_helper<t>::value> {};
template <typename t> struct is_destructible<t&>   :  true_type  {};
template <typename t> struct is_destructible<t&&>  :  true_type  {};
template <typename t> struct is_destructible<t[]>  :  false_type {};
template <>           struct is_destructible<void> :  false_type {};

/* IS_NOTHROW_DESTRUCTIBLE HELPERS */

template <typename t, bool = is_destructible<t>::value>
struct nothrow_destructible_helper
{
    static constexpr bool value = noexcept(declval<t>().~t());
};
template <typename t>
struct nothrow_destructible_helper<t, false>
{
    static constexpr bool value = false;
};

/* IS_NOTHROW_DESTRUCTIBLE IMPL */

template <typename t>        struct is_nothrow_destructible       : bool_constant<nothrow_destructible_helper<t>::value> {};
template <typename t>        struct is_nothrow_destructible<t&>   : true_type {};
template <typename t>        struct is_nothrow_destructible<t&&>  : true_type {};
template <typename t, usz n> struct is_nothrow_destructible<t[n]> : is_nothrow_destructible<t> {};

} // namespace rex::impl

namespace rex {

template <typename t>
struct is_destructible
    : impl::is_destructible<t> {};

template <typename t>
struct is_trivially_destructible
#if defined(REX_COMPILER_GCC)
    : bool_constant<__has_trivial_destructor(t)> {};
#else
    : bool_constant<__is_trivially_destructible(t)> {};
#endif

template <typename t>
struct is_nothrow_destructible
    : impl::is_nothrow_destructible<t> {};

/// @brief True if `t` is destructible, else false.
template <typename t> inline constexpr bool is_destructible_v = is_destructible<t>::value;
/// @brief True if `t` is trivially destructible, else false.
template <typename t> inline constexpr bool is_trivially_destructible_v = is_trivially_destructible<t>::value;
/// @brief True if `t` is nothrow destructible, else false.
template <typename t> inline constexpr bool is_nothrow_destructible_v = is_nothrow_destructible<t>::value;

//

template <typename t>
struct has_virtual_destructor
    : bool_constant<__has_virtual_destructor(t)> {};

/// @brief True if `t` has a virtual destructor, else false.
template <typename t> inline constexpr bool has_virtual_destructor_v = has_virtual_destructor<t>::value;

} // namespace rex