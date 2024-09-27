#pragma once

#include "rex/config.hpp"
#include "rex/types.hpp"

namespace rex
{

#if defined(REX_COMPILER_GCC)
template <usz n, usz a = alignof(double)>
struct aligned_storage
{
    struct type
    {
        char aligned_data[n];
    } __attribute__((aligned(a))); // Using aligned attribute instead of alignas
};
#else
template <usz n, usz a = alignof(double)>
struct aligned_storage
{
    struct type
    {
        alignas(a) char aligned_data[n];
    };
};
#endif

/// @brief An alias to a type that is atleast `n` bytes long and has an alignment of atleast `a`.
template <usz n, usz a = alignof(double)>
using aligned_storage_t = typename aligned_storage<n, a>::type;

} // namespace rex