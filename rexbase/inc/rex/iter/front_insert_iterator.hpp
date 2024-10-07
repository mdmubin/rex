#pragma once

#include "rex/iter/iterator_tags.hpp"
#include "rex/mem/addressof.hpp"
#include "rex/utils/move.hpp"

namespace rex
{

/// @brief An iterator to help insert elements into the front a given container using it's `push_front` member function.
/// @tparam container_t The type of container.
template <typename container_t>
class front_insert_iterator
{
  public: /* TYPEDEFS */
    using iterator_category = output_iterator_tag;
    using value_type        = void;
    using difference_type   = void;
    using pointer           = void;
    using reference         = void;
    using container_type    = container_t;
    using this_type         = front_insert_iterator<container_type>;

  protected: /* MEMBERS */
    /// @brief Pointer to the underlying container.
    container_type *m_container;

  public: /* CTORS */
    /// @brief Construct a back insert iterator for a given container.
    explicit front_insert_iterator(container_type &container)
        : m_container(addressof(container)) {}

  public: /* OPERATORS */
    this_type &operator=(typename container_type::value_type &value)  { m_container->push_front(value);       return *this; }
    this_type &operator=(typename container_type::value_type &&value) { m_container->push_front(move(value)); return *this; }

    this_type &operator* ()    { /* no-op. return self. */ return *this; }
    this_type &operator++()    { /* no-op. return self. */ return *this; }
    this_type  operator++(int) { /* no-op. return self. */ return *this; }
};

//

/// @brief Construct and return a front insert iterator using the supplied container.
template <typename container_t>
front_insert_iterator<container_t> front_inserter(container_t &container)
{
    return front_insert_iterator<container_t>{container};
}

} // namespace rex