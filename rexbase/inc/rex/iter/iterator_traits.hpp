#pragma once

#include "rex/types.hpp"
#include "rex/iter/iterator_tags.hpp"
#include "rex/traits/is_void.hpp"

namespace rex::impl
{

template <typename iter_t, typename = void>
struct iterator_traits {};

template <typename iter_t>
struct iterator_traits
<
    iter_t,
    void_t
    <
        typename iter_t::iterator_category,
        typename iter_t::value_type,
        typename iter_t::difference_type,
        typename iter_t::pointer,
        typename iter_t::reference
    >
> {
    using iterator_category = typename iter_t::iterator_category;
    using value_type        = typename iter_t::value_type;
    using difference_type   = typename iter_t::difference_type;
    using pointer           = typename iter_t::pointer;
    using reference         = typename iter_t::reference;
};

} // namespace rex::impl

namespace rex
{

/// @brief A struct that provides typedefs for identifying the properties of an iterator.
/// @tparam t The type of the iterator.
template <typename t>
struct iterator_traits : impl::iterator_traits<t> {};

/// @brief Pointer specialization for `iterator_traits`. Provides typedefs for a raw pointer based iterator.
/// @tparam t The type being pointed to by the pointer iterator.
template <typename t>
struct iterator_traits<t *>
{
    using iterator_category = random_access_iterator_tag;
    using value_type        = t;
    using difference_type   = usz;
    using pointer           = value_type *;
    using reference         = value_type &;
};

/// @brief Const pointer specialization for `iterator_traits`. Provides typedefs for a raw const pointer based iterator.
/// @tparam t The type being pointed to by the pointer iterator.
template <typename t>
struct iterator_traits<const t *>
{
    using iterator_category = random_access_iterator_tag;
    using value_type        = t;
    using difference_type   = usz;
    using pointer           = const value_type *;
    using reference         = const value_type &;
};

} // namespace rex