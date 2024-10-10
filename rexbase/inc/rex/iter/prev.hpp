#pragma once

#include "rex/iter/advance.hpp"
#include "rex/iter/iterator_traits.hpp"

namespace rex
{

/// @brief Get the `n`-th previous iterator.
/// @tparam iter_t The type of the iterator.
/// @param iter The iterator.
/// @param n The number of steps `iter` is to move backwards. Defaults to 1.
/// @return The iterator advanced by `-n`.
template <typename iter_t>
constexpr iter_t prev(iter_t iter, typename iterator_traits<iter_t>::difference_type n = 1)
{
    advance(iter, -n);
    return iter;
}

} // namespace rex