#pragma once

#include "rex/traits/decay.hpp"
#include "rex/utils/declval.hpp"

namespace rex {

template <typename...>
struct common_type
{
    /* sizeof...(t) == 0, common type undefined. */
};
template <typename t>
struct common_type<t> : common_type<t, t>
{
    /* sizeof...(t) == 1, common type between two `t`s. */
};
template <typename t, typename u>
struct common_type<t, u>
{
    /* sizeof...(t) == 2, decayed type of a common type set by the compiler. */
    using type = decay_t<decltype(false ? declval<t>() : declval<u>())>;
};
template <typename t, typename u, typename... rest>
struct common_type<t, u, rest...>
{
    /* sizeof...(t) > 2, common type is common( common(t, u), rest... ) */
    using type = typename common_type<typename common_type<t, u>::type, rest...>::type;
};

/// @brief An alias to a type such that all types in `...t` can be implicitly converted to if such a type exists.
template <typename... t>
using common_type_t = typename common_type<t...>::type;

} // namespace rex