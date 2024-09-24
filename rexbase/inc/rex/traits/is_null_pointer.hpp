#pragma once

#include "rex/traits/integral_constant.hpp"
#include "rex/traits/is_const_volatile.hpp"
#include "rex/traits/is_same.hpp"

namespace rex {

template <typename t> struct is_null_pointer
    : bool_constant<is_same_v<remove_cv_t<t>, decltype(nullptr)>> {};

/// @brief True if `t` is std::nullptr_t, else false. 
template <typename t> inline constexpr bool is_null_pointer_v = is_null_pointer<t>::value;

} // namespace rex