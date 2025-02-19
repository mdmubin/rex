#pragma once

#include "rex/numeric/abs.hpp"
#include "rex/traits/common_type.hpp"
#include "rex/traits/is_integral.hpp"
#include "rex/traits/is_same.hpp"

namespace rex
{

/// @brief Calculate and return the greatest common divisor of two values, `valA` and `valB`.
/// @tparam t The type of `valA`, expected to be a non-boolean integral type.
/// @tparam u The type of `valB`, expected to be a non-boolean integral type.
/// @tparam r The return type, defaults to `common_type_t<t, u>`.
template <typename t, typename u, typename r = common_type_t<t, u>>
constexpr r gcd(t valA, u valB)
{
    static_assert(is_integral_v<t> && is_integral_v<u>, "Types `t` and `u` must be integral types.");
    static_assert(!is_same_v<t, bool> && !is_same_v<u, bool>, "Types `t` and `u` may not be boolean types.");

    if (valA == 0 || valB == 0)
    {
        return valA > valB ? valA : valB;
    }

    valA = abs(valA);
    valB = abs(valB);

    r temp{};
    while (valB != 0)
    {
        temp = valB;
        valB = valA % valB;
        valA = temp;
    }

    return static_cast<r>(valA);
}

} // namespace rex