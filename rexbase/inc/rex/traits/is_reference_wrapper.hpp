#pragma once

#include "rex/traits/integral_constant.hpp"

namespace rex {

/* forward decl of reference_wrapper */
template <typename t> struct reference_wrapper;

// Non-standard traits

template <typename t> struct is_reference_wrapper                       : false_type {};
template <typename t> struct is_reference_wrapper<reference_wrapper<t>> : true_type  {};

/// @brief True if `t` is a `reference_wrapper` type, else false.
template <typename t> inline constexpr bool is_reference_wrapper_v = is_reference_wrapper<t>::value;

} // namespace rex