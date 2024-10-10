#pragma once

#include "rex/types.hpp"

namespace rex
{

/// @brief A struct that provides typedefs for helping with iterator implementations.
/// @tparam c The iterator category.
/// @tparam t The type of the values being iterated over.
/// @tparam d The difference type between two iterators. Default `rex::isz`.
/// @tparam p The pointer type for the values being iterated over.
/// @tparam r The reference type for the values being iterated over.
template <typename c, typename t, typename d = isz, typename p = t *, typename r = t &>
struct iterator
{
    using iterator_category = c;
    using value_type        = t;
    using difference_type   = d;
    using pointer           = p;
    using reference         = r;
};

} // namespace rex