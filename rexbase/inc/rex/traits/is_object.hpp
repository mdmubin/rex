#pragma once

#include "rex/traits/integral_constant.hpp"
#include "rex/traits/is_array.hpp"
#include "rex/traits/is_class.hpp"
#include "rex/traits/is_scalar.hpp"
#include "rex/traits/is_union.hpp"

namespace rex {

template <typename t> struct is_object
    : bool_constant<is_array_v<t> || is_class_v<t> || is_scalar_v<t> || is_union_v<t>> {};

/// @brief True if `t` is an object type, else false. 
template <typename t> inline constexpr bool is_object_v = is_object<t>::value;

} // namespace rex