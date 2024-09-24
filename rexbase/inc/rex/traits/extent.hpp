#pragma once

#include "rex/types.hpp"
#include "rex/traits/integral_constant.hpp"

namespace rex {

template <class t, unsigned n = 0> struct extent
    : integral_constant<usz, 0> {};

template <class t> struct extent<t[], 0>
    : integral_constant<usz, 0> {};

template <class t, unsigned n> struct extent<t[], n>
    : extent<t, n - 1> {};

template <class t, usz l> struct extent<t[l], 0>
    : integral_constant<usz, l> {};

template <class t, usz l, unsigned n> struct extent<t[l], n>
    : extent<t, n - 1> {};

/// @brief The number of elements in the `n`-th dimension, for type `t`. 
template <typename t, unsigned n = 0> inline constexpr usz extent_v = extent<t, n>::value;

} // namespace rex