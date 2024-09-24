#include <gtest/gtest.h>
#include <rex/type_traits.hpp>

// clang-format off
using namespace rex;

// is same
static_assert(
        is_same_v<int, int>
    &&  is_same_v<i32, int32_t>
    &&  is_same_v<const int*, int const*>
    && !is_same_v<const int, const volatile int>
);
// is const-volatile
static_assert(
        is_const_v<const int>
    &&  is_const_v<const volatile int>
    &&  is_const_v<int const>
    && !is_const_v<int>
    && !is_const_v<volatile int>
    &&  is_volatile_v<volatile int>
    &&  is_volatile_v<const volatile int>
    &&  is_volatile_v<int volatile>
    && !is_volatile_v<int>
    && !is_volatile_v<const int>
);
// remove const volatile
static_assert(
       is_same_v<int, remove_const_t<int>>
    && is_same_v<int, remove_const_t<const int>>
    && is_same_v<int, remove_volatile_t<int>>
    && is_same_v<int, remove_volatile_t<int volatile>>
    && is_same_v<int, remove_cv_t<int>>
    && is_same_v<int, remove_cv_t<const int>>
    && is_same_v<int, remove_cv_t<volatile int>>
    && is_same_v<int, remove_cv_t<const volatile int>>
);
// add const volatile
static_assert(
       is_same_v<const int,          add_const_t<int>>
    && is_same_v<const int,          add_const_t<const int>>
    && is_same_v<volatile const int, add_const_t<volatile int>>
    && is_same_v<volatile int,       add_volatile_t<int>>
    && is_same_v<volatile int,       add_volatile_t<volatile int>>
    && is_same_v<const volatile int, add_volatile_t<const int>>
);
// match const volatile
static_assert(
       is_same_v<int,                match_cv_t<int, int>>
    && is_same_v<const int,          match_cv_t<const int, int>>
    && is_same_v<const volatile int, match_cv_t<const volatile int, int>>
    && is_same_v<const volatile int, match_cv_t<const volatile int, const volatile int>>
);