#pragma once

#include "rex/iter/iterator_traits.hpp"
#include "rex/mem/addressof.hpp"

namespace rex
{

/// @brief An adaptor for an iterator that reverses the direction of the iteration.
/// @tparam i The iterator type.
template <typename iter_t>
class reverse_iterator
{
  public: /* TYPEDEFS */
    using iterator_type     = iter_t;
    using this_type         = reverse_iterator<iter_t>;
    using iterator_category = typename iterator_traits<iterator_type>::iterator_category;
    using value_type        = typename iterator_traits<iterator_type>::value_type;
    using difference_type   = typename iterator_traits<iterator_type>::difference_type;
    using pointer           = typename iterator_traits<iterator_type>::pointer;
    using reference         = typename iterator_traits<iterator_type>::reference;

  protected: /* MEMBERS */
    /// @brief The underlying iterator.
    iterator_type m_iterator;

  public: /* CTORS */
    /// @brief Default construct a reverse iterator
    constexpr reverse_iterator()
        : m_iterator() {}

    /// @brief Construct a reverse iterator with the given underlying iterator.
    constexpr explicit reverse_iterator(iterator_type iter)
        : m_iterator(iter) {}

    /// @brief Construct a reverse iterator using the base iterator from `other`.
    template <typename other_t>
    constexpr explicit reverse_iterator(const reverse_iterator<other_t> &other)
        : m_iterator(other.base()) {}

  public: /* METHODS */
    /// @brief Get the underlying base iterator.
    constexpr iterator_type base() const { return m_iterator; }

  public: /* OPERATORS */
    template <typename other_t>
    constexpr this_type &operator=(const reverse_iterator<other_t> &other)
    {
        m_iterator = other.base();
        return *this;
    }

    constexpr reference operator*() const { auto tmp = m_iterator; return *(--tmp); }

    constexpr reference operator->() const { return addressof(operator*()); }

    constexpr reference operator[](difference_type n) const { return m_iterator[-n - 1]; }

    constexpr this_type &operator++() { --m_iterator; return *this; }
    constexpr this_type &operator--() { ++m_iterator; return *this; }

    constexpr this_type operator++(int) { auto tmp = *this; --m_iterator; return tmp; }
    constexpr this_type operator--(int) { auto tmp = *this; ++m_iterator; return tmp; }

    constexpr this_type operator+(difference_type n) const { return this_type{m_iterator - n}; }
    constexpr this_type operator-(difference_type n) const { return this_type{m_iterator + n}; }

    constexpr this_type &operator+=(difference_type n) { m_iterator -= n; return *this; }
    constexpr this_type &operator-=(difference_type n) { m_iterator += n; return *this; }
};

//

/// @brief Construct and return a reverse iterator using the supplied iterator.
template <typename iter_t>
constexpr reverse_iterator<iter_t> make_reverse_iterator(iter_t iter)
{
    return reverse_iterator<iter_t>{iter};
}

//

template <typename i, typename j>
constexpr bool operator==(const reverse_iterator<i> &l, const reverse_iterator<j> &r)
{
    return l.base() == r.base();
}
template <typename i, typename j>
constexpr bool operator!=(const reverse_iterator<i> &l, const reverse_iterator<j> &r)
{
    return l.base() != r.base();
}
template <typename i, typename j>
constexpr bool operator<(const reverse_iterator<i> &l, const reverse_iterator<j> &r)
{
    return l.base() > r.base();
}
template <typename i, typename j>
constexpr bool operator<=(const reverse_iterator<i> &l, const reverse_iterator<j> &r)
{
    return l.base() >= r.base();
}
template <typename i, typename j>
constexpr bool operator>(const reverse_iterator<i> &l, const reverse_iterator<j> &r)
{
    return l.base() < r.base();
}
template <typename i, typename j>
constexpr bool operator>=(const reverse_iterator<i> &l, const reverse_iterator<j> &r)
{
    return l.base() <= r.base();
}

template <typename i>
constexpr reverse_iterator<i> operator+(typename reverse_iterator<i>::difference_type n, const reverse_iterator<i> &r)
{
    return reverse_iterator<i>{r.base() - n};
}
template <typename i>
constexpr reverse_iterator<i> operator-(typename reverse_iterator<i>::difference_type n, const reverse_iterator<i> &r)
{
    return reverse_iterator<i>{r.base() + n};
}

} // namespace rex