#pragma once

namespace rex {

/// @brief Enables compile-time traits deduction.
template <typename val_t, val_t val>
struct integral_constant {
    using value_type = val_t;
    using type = integral_constant<value_type, val>;

    static constexpr value_type value = val;

    constexpr explicit operator value_type() const noexcept { return value; }
    constexpr value_type operator()() const noexcept { return value; }
};

/// @brief Alias to an integral constant dealing with boolean values.
/// @tparam value The boolean value. Either `true` or `false`.
template <bool value> using bool_constant = integral_constant<bool, value>;

/// @brief True type boolean integral constant.
using true_type = bool_constant<true>;
/// @brief False type boolean integral constant.
using false_type = bool_constant<false>;

} // namespace rex