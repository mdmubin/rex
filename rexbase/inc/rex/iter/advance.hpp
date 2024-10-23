#pragma once

#include "rex/iter/iterator_tags.hpp"
#include "rex/iter/iterator_traits.hpp"

namespace rex::impl
{

template <typename i>
constexpr void advance(i &iter, typename iterator_traits<i>::difference_type n, input_iterator_tag)
{
    for (; n > 0; --n)
    {
        ++iter;
    }
}

template <typename i>
constexpr void advance(i &iter, typename iterator_traits<i>::difference_type n, bidirectional_iterator_tag)
{
    if (n > 0)
    {
        for (; n > 0; --n)
        {
            ++iter;
        }
    }
    else
    {
        for (; n < 0; ++n)
        {
            --iter;
        }
    }
}

template <typename i>
constexpr void advance(i &iter, typename iterator_traits<i>::difference_type n, random_access_iterator_tag)
{
    iter += n;
}

} // namespace rex::impl

namespace rex
{

/// @brief Increment the iterator by the given distance. If the distance is negative, the iterator is decremented.
/// @tparam iter_t Type of the iterator.
/// @tparam distance_t Distance type. Expected to be convertible to `iterator_traits<iter_t>::difference_type`.
/// @param iter The iterator being advanced.
/// @param distance The distance by which the iterator will be advanced.
/// @note If the iterator is not atleast a bidirectional iterator, and the given distance is less than zero, then the
/// iterator is not advanced.
template <typename iter_t, typename distance_t>
constexpr void advance(iter_t &iter, distance_t distance)
{
    using iter_diff = typename iterator_traits<iter_t>::difference_type;
    using iter_tag  = typename iterator_traits<iter_t>::iterator_category;
    impl::advance(iter, iter_diff(distance), iter_tag());
}

} // namespace rex