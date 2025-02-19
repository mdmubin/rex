#pragma once

#include "rex/numeric/gcd.hpp"
#include "rex/types.hpp"

namespace rex
{

/// @brief Represents a ratio in the form of `n/d`.
/// @tparam n The numerator value, defaults to 0.
/// @tparam d The denominator value, defaults to 1.
template <i64 n = 0, i64 d = 1>
class ratio
{
  public: /* STATIC MEMBERS */
    /// @brief Numerator value, reduced by dividing it with `gcd(n, d)`.
    static constexpr i64 num = n * (d < 0 ? -1 : 1) / gcd(n, d);
    /// @brief Denominator value, reduced by dividing it with `gcd(n, d)`.
    static constexpr i64 den = d * (d < 0 ? -1 : 1) / gcd(n, d);

  public: /* TYPEDEFS */
    using type = ratio<num, den>;

  public: /* ASSERTIONS */
    static_assert(d != 0, "Denominator may not be zero.");
    static_assert(n != INT64_MIN && d != INT64_MIN, "Values for numerator/denominator are out of range.");
};

} // namespace rex