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

//

template <typename t>        struct remove_extent       { using type = t; };
template <typename t>        struct remove_extent<t[]>  { using type = t; };
template <typename t, usz l> struct remove_extent<t[l]> { using type = t; };

/// @brief if `t` is an array, then this type aliases the type of the element of `t`, else it aliases `t` itself.
template <typename t> using remove_extent_t = typename remove_extent<t>::type;

//

template <typename t>        struct remove_all_extents       { using type = t; };
template <typename t>        struct remove_all_extents<t[]>  { using type = typename remove_all_extents<t>::type; };
template <typename t, usz l> struct remove_all_extents<t[l]> { using type = typename remove_all_extents<t>::type; };

/// @brief If `t` is a multidimensional array of `elem_t`, then this type aliases `elem_t`, else it aliases `t` itself.
template <typename t> using remove_all_extents_t = typename remove_all_extents<t>::type;

} // namespace rex