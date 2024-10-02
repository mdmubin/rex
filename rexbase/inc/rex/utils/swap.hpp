#pragma once

#include "rex/types.hpp"
#include "rex/traits/enable_if.hpp"
#include "rex/traits/is_swappable.hpp"
#include "rex/utils/move.hpp"

namespace rex
{

/// @brief Swap between two values, if `t` is can move constructed and move assigned.
template <typename t, typename = enable_if_t<is_swappable_v<t>>>
void swap(t &valueA, t &valueB) noexcept(is_nothrow_swappable_v<t>)
{
    auto x = move(valueA);
    valueA = move(valueB);
    valueB = move(x);
}

/// @brief Swap contents of two fixed sized arrays of length`l`, if two elements of type `t` can swapped.
template <typename t, usz l, typename = enable_if_t<is_swappable_v<t>>>
void swap(t (&valueA)[l], t (&valueB)[l]) noexcept(is_nothrow_swappable_v<t>)
{
    for (usz i = 0; i < l; i++)
    {
        swap(valueA[i], valueB[i]);
    }
}

} // namespace rex