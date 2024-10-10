#pragma once

#include "rex/iter/iterator_tags.hpp"
#include "rex/iter/iterator_traits.hpp"

namespace rex::impl
{

template <typename i, typename d = typename iterator_traits<i>::difference_type>
constexpr d distance(i first, i last, input_iterator_tag)
{
    d dist = 0;

    for (; first != last; ++first)
    {
        ++dist;
    }

    return dist;
}

template <typename i, typename d = typename iterator_traits<i>::difference_type>
constexpr d distance(i first, i last, random_access_iterator_tag)
{
    return last - first;
}

} // namespace rex::impl

namespace rex
{

/// @brief Get the distance between the two iterators. (i.e. number of elements traversed to reach `last` from `first`).
/// @tparam iter_t The type of iterator.
/// @param first The iterator from which the distance is being measured.
/// @param last The iterator to which the distance will be measured.
/// @return The distance between the two iterators. May be negative for random access iterators.
/// @note If `iter_t` is a random access iterator type, then `last - first` is expected to be valid. Else, `last` is
/// expected to be reachable by incrementing `first`.
template <typename iter_t>
constexpr typename iterator_traits<iter_t>::difference_type distance(iter_t first, iter_t last)
{
    using iter_tag = typename iterator_traits<iter_t>::iterator_category;
    return impl::distance(first, last, iter_tag());
}

} // namespace rex