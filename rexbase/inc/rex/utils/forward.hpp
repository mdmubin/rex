#pragma once

#include "rex/traits/is_reference.hpp"

namespace rex
{

/// @brief Forward an lvalue as an lvalue or an rvalue.
template <typename value_t>
constexpr value_t &&forward(remove_reference_t<value_t> & value) noexcept
{
    return static_cast<value_t &&>(value);
}

/// @brief Forward an rvalue as an rvalue, and prevents forwarding as an lvalue.
template <typename value_t>
constexpr value_t &&forward(remove_reference_t<value_t> &&value) noexcept
{
    static_assert(!is_lvalue_reference_v<value_t>, "Cannot convert an rvalue to an lvalue.");
    return static_cast<value_t &&>(value);
}

} // namespace  rex
