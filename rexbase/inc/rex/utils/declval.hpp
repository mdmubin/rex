#pragma once

#include "rex/traits/is_reference.hpp"

namespace rex
{

/// @brief Utility function meant to be used an unevaluated context to convert `t` to an rvalue reference type.
template <typename t>
add_rvalue_reference_t<t> declval() noexcept;

} // namespace rex