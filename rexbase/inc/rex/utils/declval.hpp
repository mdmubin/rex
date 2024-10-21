#pragma once

#include "rex/traits/is_reference.hpp"

namespace rex::impl
{

template <typename>
struct declval_assert_value
{
    static constexpr bool value = false;
};

} // namespace rex::impl

namespace rex
{

template <typename t>
add_rvalue_reference_t<t> declval() noexcept
{
    static_assert(impl::declval_assert_value<t>::value, "declval() must not be evaluated!");
}

} // namespace rex