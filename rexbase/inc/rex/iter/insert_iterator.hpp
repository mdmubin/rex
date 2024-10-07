#pragma once

#include "rex/iter/iterator_tags.hpp"
#include "rex/mem/addressof.hpp"
#include "rex/utils/move.hpp"

namespace rex
{

/// @brief An iterator to help with inserting elements into a given container using it's `insert` member function, at
/// the position of the supplied iterator. The positional iterator is advanced with each insertion.
/// @tparam container_t The type of container.
template <typename container_t>
class insert_iterator
{
  public: /* TYPEDEFS */
    using iterator        = output_iterator_tag;
    using value_type      = void;
    using difference_type = void;
    using pointer         = void;
    using reference       = void;
    using container_type  = container_t;
    using this_type       = insert_iterator<container_type>;

  protected: /* MEMBERS */
    /// @brief Pointer to te underlying container.
    container_type *m_container;
    /// @brief An iterator for the container.
    typename container_type::iterator m_iterator;

  public: /* CTORS */
    /// @brief Construct an insert iterator to a given container using an iterator to that container.
    insert_iterator(container_type &container, typename container_type::iterator iter)
        : m_container(addressof(container)), m_iterator(iter) {}

  public: /* METHODS */
    this_type &operator=(typename container_type::value_type &value)
    {
        m_iterator = m_container->insert(m_iterator, value);
        ++m_iterator;
        return *this;
    }

    this_type &operator=(typename container_type::value_type &&value)
    {
        m_iterator = m_container->insert(m_iterator, move(value));
        ++m_iterator;
        return *this;
    }

    this_type &operator* () { /* no-op. return self. */ return *this; }
    this_type &operator++() { /* no-op. return self. */ return *this; }
    this_type &operator--() { /* no-op. return self. */ return *this; }
};

//


/// @brief Construct and return an insert iterator using the supplied container and iterator.
template <typename container_t>
insert_iterator<container_t> make_inserter(container_t &container, typename container_t::iterator iter)
{
    return insert_iterator<container_t>{container, iter};
}

} // namespace rex