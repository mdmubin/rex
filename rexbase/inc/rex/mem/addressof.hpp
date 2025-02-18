#pragma once

namespace rex
{

/// @brief Get the address of `value`.
template <typename t>
constexpr t *addressof(t &value) noexcept
{
    // return reinterpret_cast<t *>(&const_cast<char &>(reinterpret_cast<const volatile char &>(value)));
    return __builtin_addressof(value); /* cannot be constexpr without compiler support. */
}

/// @brief Taking address of rvalue types is not allowed.
template <typename t>
const t *addressof(const t &&) = delete;

} // namespace rex