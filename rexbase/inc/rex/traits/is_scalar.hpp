#pragma once

#include "rex/traits/integral_constant.hpp"
#include "rex/traits/is_arithmetic.hpp"
#include "rex/traits/is_enum.hpp"
#include "rex/traits/is_member_pointer.hpp"
#include "rex/traits/is_null_pointer.hpp"
#include "rex/traits/is_pointer.hpp"

namespace rex {
    
template <typename t> struct is_scalar
    : bool_constant
    <
        is_arithmetic_v<t> || is_enum_v<t> || is_member_pointer_v<t> || is_null_pointer_v<t> || is_pointer_v<t>
    > {};

/// @brief True if `t` is a scalar type, else false. 
template <typename t> inline constexpr bool is_scalar_v = is_scalar<t>::value;

} // namespace rex