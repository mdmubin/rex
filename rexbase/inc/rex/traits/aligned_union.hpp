#pragma once

#include "rex/types.hpp"
#include "rex/algo/max.hpp"

namespace rex
{

template <usz n, typename... t>
struct aligned_union
{
    static constexpr usz alignment_value = max({alignof(t)...});

    struct type
    {
        alignas(alignment_value) char data[max({n, sizeof(t)...})];
    };
};

/// @brief An alias to a type that is atleast `n` bytes long, and can store values of any type from `...t`.
template <usz n, typename... t> using aligned_union_t = typename aligned_union<n, t...>::type;

} // namespace rex