#pragma once

#include <initializer_list>

#include "rex/iter/reverse_iterator.hpp"
#include "rex/types.hpp"

namespace rex
{

/* BEGIN */

/// @brief Get an iterator to the beginning of the given container.
template <typename container_t>
constexpr auto begin(container_t &container) -> decltype(container.begin())
{
    return container.begin();
}

/// @brief Get a const iterator to the beginning of the given container.
template <typename container_t>
constexpr auto begin(const container_t &container) -> decltype(container.begin())
{
    return container.begin();
}

/// @brief Get an iterator to the beginning of an array of elements of type `elem_t` and size `arrlen`.
template <typename elem_t, usz arrlen>
constexpr elem_t *begin(elem_t (&array)[arrlen]) noexcept
{
    return array;
}

/// @brief Get a const iterator to the beginning of the given container.
template <typename container_t>
constexpr auto cbegin(const container_t &container) noexcept(noexcept(begin(container))) -> decltype(begin(container))
{
    return begin(container);
}

/* END */

/// @brief Get an iterator to the end of the given container.
template <typename container_t>
constexpr auto end(container_t &container) -> decltype(container.end())
{
    return container.end();
}

/// @brief Get a const iterator to the end of the given container.
template <typename container_t>
constexpr auto end(const container_t &container) -> decltype(container.end())
{
    return container.end();
}

/// @brief Get an iterator to the end of an array of elements of type `elem_t` and size `arrlen`.
template <typename elem_t, usz arrlen>
constexpr elem_t *end(elem_t (&array)[arrlen]) noexcept
{
    return array + arrlen;
}

/// @brief Get a const iterator to the end of the given container.
template <typename container_t>
constexpr auto cend(const container_t &container) noexcept(noexcept(end(container))) -> decltype(container.end())
{
    return end(container);
}

/* RBEGIN */

/// @brief Get an reverse iterator to the beginning of the given container.
template <typename container_t>
constexpr auto rbegin(container_t &container) -> decltype(container.rbegin())
{
    return container.rbegin();
}

/// @brief Get a const reverse iterator to the beginning of the given container.
template <typename container_t>
constexpr auto rbegin(const container_t &container) -> decltype(container.rbegin())
{
    return container.rbegin();
}

/// @brief Get a reverse iterator to the beginning of an array of elements of type `elem_t` and size `arrlen`.
template <typename elem_t, usz arrlen>
constexpr reverse_iterator<elem_t *> rbegin(elem_t (&array)[arrlen]) noexcept
{
    return reverse_iterator<elem_t *>{array + arrlen};
}

/// @brief Get a reverse iterator to the beginning of an initializer list.
template <typename elem_t>
constexpr reverse_iterator<const elem_t *> rbegin(std::initializer_list<elem_t> iList)
{
    return reverse_iterator<const elem_t *>(iList.begin());
}

/// @brief Get a const reverse iterator to the beginning of the given container.
template <typename container_t>
constexpr auto crbegin(const container_t &container) noexcept(noexcept(rbegin(container)))
    -> decltype(rbegin(container))
{
    return rbegin(container);
}

/* REND */

/// @brief Get an reverse iterator to the end of the given container.
template <typename container_t>
constexpr auto rend(container_t &container) -> decltype(container.rend())
{
    return container.rend();
}

/// @brief Get a const reverse iterator to the end of the given container.
template <typename container_t>
constexpr auto rend(const container_t &container) -> decltype(container.rend())
{
    return container.rend();
}

/// @brief Get an reverse iterator to the end of an array of elements of type `elem_t` and size `arrlen`.
template <typename elem_t, usz arrlen>
constexpr reverse_iterator<elem_t *> rend(elem_t (&array)[arrlen]) noexcept
{
    return reverse_iterator<elem_t *>{array};
}

/// @brief Get a reverse iterator to the end of the initializer list.
template <typename elem_t>
constexpr reverse_iterator<const elem_t *> rend(std::initializer_list<elem_t> iList)
{
    return reverse_iterator<const elem_t *>(iList.end());
}

/// @brief Get a const reverse iterator to the end of the given container.
template <typename container_t>
constexpr auto crend(const container_t &container) noexcept(noexcept(rend(container))) -> decltype(container.rend())
{
    return rend(container);
}

/* SIZE */

/// @brief Get the size of a container.
template <typename container_t>
constexpr auto size(const container_t &container) -> decltype(container.size())
{
    return container.size();
}

/// @brief Get the size of an array of elements of type `elem_t` and size `arrlen`.
template <typename elem_t, usz arrlen>
constexpr auto size(const elem_t (&array)[arrlen]) noexcept
{
    REX_UNUSED(array);
    return arrlen;
}

/* EMPTY */

/// @brief Check whether the given container is empty or not.
template <typename container_t>
constexpr auto empty(const container_t &container) -> decltype(container.empty())
{
    return container.empty();
}

/// @brief Check whether an array is empty or not. This always returns false.
template <typename elem_t, usz arrlen>
constexpr bool empty(const elem_t (&array)[arrlen])
{
    REX_UNUSED(array);
    return false;
}

/// @brief Check whether an initializer list is empty or not.
template <typename elem_t>
constexpr bool empty(std::initializer_list<elem_t> iList) noexcept
{
    return iList.size() == 0;
}

/* DATA */

/// @brief Get the underlying data of the given container.
template <typename container_t>
constexpr auto data(container_t &container) -> decltype(container.data())
{
    return container.data();
}

/// @brief Get the underlying const data of the given container.
template <typename container_t>
constexpr auto data(const container_t &container) -> decltype(container.data())
{
    return container.data();
}

/// @brief Pointer to the beginning of the array.
template <typename elem_t, usz arrlen>
constexpr elem_t *data(elem_t (&array)[arrlen]) noexcept
{
    return array;
}

/// @brief Pointer to the beginning of the initializer list.
template <typename elem_t>
constexpr elem_t *data(std::initializer_list<elem_t> iList) noexcept
{
    return iList.begin();
}

} // namespace rex