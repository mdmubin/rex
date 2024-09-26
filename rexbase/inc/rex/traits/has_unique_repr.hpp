#pragma once

#include "rex/traits/integral_constant.hpp"

namespace rex {

template <typename t>
struct has_unique_object_representations
    : bool_constant<__has_unique_object_representations(t)> {};

/// @brief True if `t` has unique object representations, else false.
template <typename t> inline constexpr bool has_unique_object_representations_v = has_unique_object_representations<t>::value;

} // namespace rex