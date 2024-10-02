#pragma once

#include "rex/traits/conditional.hpp"
#include "rex/traits/is_reference.hpp"
#include "rex/traits/is_constructible.hpp"

namespace rex::impl
{

/// @brief The return type for `move_if_noexcept`, conditionally enabling either a copy return or a move return.
template <typename t, bool copy_or_move = (!is_nothrow_constructible_v<t> && is_copy_constructible_v<t>)>
using move_if_noexcept_t = conditional_t<copy_or_move, const t &, t &&>;

} // namespace rex::impl

namespace rex
{

/// @brief Convert the given value into an rvalue reference, enabling it to be moved.
template <typename value_t>
constexpr remove_reference_t<value_t> &&move(value_t &&value) noexcept
{
    return static_cast<remove_reference_t<value_t> &&>(value);
}

/// @brief If the move constructor in `value_t` could throw an exception and the type is copyable, a const lvalue
/// reference is returned. Otherwise, it is the same as `move(value)`.
template <typename value_t>
constexpr impl::move_if_noexcept_t<value_t> move_if_noexcept(value_t &value) noexcept
{
    return move(value);
}

} // namespace rex