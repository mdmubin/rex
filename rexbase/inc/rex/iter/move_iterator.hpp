#pragma once

#include "rex/iter/iterator_tags.hpp"
#include "rex/iter/iterator_traits.hpp"
#include "rex/traits/conditional.hpp"
#include "rex/traits/is_reference.hpp"
#include "rex/utils/move.hpp"

namespace rex
{

/// @brief An iterator where dereferencing causes the value to be converted to an rvalue, allowing it to be moved.
/// @tparam iter_t The underlying iterator type.
template <typename iter_t>
struct move_iterator
{
  private: /* TYPEDEFS */
    using iter_ref = typename iterator_traits<iter_t>::reference;

  public: /* TYPEDEFS */
    using iterator_type     = iter_t;
    using this_type         = move_iterator<iterator_type>;
    using iterator_category = typename iterator_traits<iterator_type>::iterator_category;
    using value_type        = typename iterator_traits<iterator_type>::value_type;
    using difference_type   = typename iterator_traits<iterator_type>::difference_type;
    using pointer           = iterator_type;
    using reference         = conditional_t<is_reference_v<iter_ref>, remove_reference_t<iter_ref> &&, iter_ref>;

  protected: /* MEMBERS */
    /// @brief Underlying iterator.
    iterator_type m_iterator;

  public: /* CTORS */
    /// @brief Default construct a move iterator.
    constexpr move_iterator()
        : m_iterator() {}

    /// @brief Construct a move iterator with the given underlying iterator.
    constexpr explicit move_iterator(iterator_type iter)
        : m_iterator(iter) {}

    /// @brief Construct a move iterator with the base iterator of `other`.
    template <typename other_t>
    constexpr move_iterator(const move_iterator<other_t> &other)
        : m_iterator(other.base()) {}

  public: /* METHODS */
    /// @brief Get the underlying iterator.
    constexpr iterator_type base() const { return m_iterator; }

  public: /* OPERATORS */
    template <typename other_t>
    constexpr this_type &operator=(const move_iterator<other_t> &other)
    {
        m_iterator = other.base();
        return *this;
    }

    constexpr reference operator*() const { return static_cast<reference>(*m_iterator); }

    constexpr pointer operator->() const { return m_iterator; }

    constexpr reference operator[](difference_type n) const { return move(m_iterator[n]); }

    constexpr this_type &operator++() { ++m_iterator; return *this; }
    constexpr this_type &operator--() { --m_iterator; return *this; }

    constexpr this_type operator++(int) { auto tmp = *this; ++m_iterator; return tmp; }
    constexpr this_type operator--(int) { auto tmp = *this; --m_iterator; return tmp; }

    constexpr this_type operator+(difference_type n) const { return this_type{m_iterator + n}; }
    constexpr this_type operator-(difference_type n) const { return this_type{m_iterator - n}; }

    constexpr this_type &operator+=(difference_type n) { m_iterator += n; return *this; }
    constexpr this_type &operator-=(difference_type n) { m_iterator -= n; return *this; }
};

//

/// @brief Construct and return a move iterator using the given iterator.
template <typename iter_t>
move_iterator<iter_t> make_move_iterator(iter_t iter)
{
    return move_iterator<iter_t>{iter};
}

//

template <typename i, typename j>
constexpr bool operator==(const move_iterator<i> &l, const move_iterator<j> &r)
{
    return l.base() == r.base();
}
template <typename i, typename j>
constexpr bool operator!=(const move_iterator<i> &l, const move_iterator<j> &r)
{
    return !(l == r);
}
template <typename i, typename j>
constexpr bool operator<(const move_iterator<i> &l, const move_iterator<j> &r)
{
    return l.base() < r.base();
}
template <typename i, typename j>
constexpr bool operator<=(const move_iterator<i> &l, const move_iterator<j> &r)
{
    return !(r < l);
}
template <typename i, typename j>
constexpr bool operator>(const move_iterator<i> &l, const move_iterator<j> &r)
{
    return r < l;
}
template <typename i, typename j>
constexpr bool operator>=(const move_iterator<i> &l, const move_iterator<j> &r)
{
    return !(l < r);
}

template <typename i>
constexpr move_iterator<i> operator+(typename move_iterator<i>::difference_type n, const move_iterator<i> &m)
{
    return m + n;
}
template <typename i>
constexpr move_iterator<i> operator-(typename move_iterator<i>::difference_type n, const move_iterator<i> &m)
{
    return m - n;
}

} // namespace rex