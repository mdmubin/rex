#pragma once

#include "rex/traits/is_enum.hpp"

namespace rex::impl {
template <typename t, bool = is_enum_v<t>> struct underlying_type         {};
template <typename t>                      struct underlying_type<t, true>{ using type = __underlying_type(t); };
} // namespace rex::impl

namespace rex {

template <typename t> struct underlying_type { using type = typename impl::underlying_type<t>::type; };

/// @brief An alias to the underlying type of `t` if `t` is an enum, else undefined.
template <typename t> using underlying_type_t = typename underlying_type<t>::type;

} // namespace rex