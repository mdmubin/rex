#pragma once

#include "rex/types.hpp"
#include "rex/traits/integral_constant.hpp"

namespace rex {

template <typename t> struct alignment_of
    : integral_constant<usz, alignof(t)> {};

/// @brief The alignment value of type `t`.
template <typename t> inline constexpr usz alignment_of_v = alignment_of<t>::value; 

} // namespace rex