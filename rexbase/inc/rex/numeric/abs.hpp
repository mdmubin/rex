#pragma once

namespace rex
{

/// @brief Returns the absolute value of `value`.
/// @tparam t The type of `value`.
/// @tparam r The return type of |value|, defaults to `t`.
template <typename t, typename r = t>
constexpr r abs(t value)
{
    return static_cast<r>(value >= 0 ? value : -value);
}

} // namespace rex