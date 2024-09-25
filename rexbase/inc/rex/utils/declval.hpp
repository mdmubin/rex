#pragma once

#include "rex/traits/is_reference.hpp"

namespace rex
{

/// @brief Utility function meant to be used an unevaluated context to convert `t` to an rvalue reference type.
/// @return May not be called, as doing so results in a `static_assert` fail.
template <typename t>
add_rvalue_reference_t<t> declval() noexcept
{
    static_assert(false, "rex::declval may not be evaluated.");
}

} // namespace rex