#pragma once

#include "rex/types.hpp"

namespace rex::impl
{

template <typename t>
struct atomic_storage_traits
{ // clang-format off
    static constexpr usz size = sizeof(t) == 1 ? 1
        : sizeof(t) == 2  ? 2
        : sizeof(t) <= 4  ? 4
        : sizeof(t) <= 8  ? 8
        : sizeof(t) <= 16 ? 16
        : sizeof(t);
    static constexpr usz padding = size - sizeof(t);

    static_assert(size <= 16 && size > 0, "Atomic operations are not currently if sizeof(t) > 16 or sizeof(t) == 0.");
}; // clang-format on

template <typename t, bool padded = (atomic_storage_traits<t>::padding > 0)>
struct atomic_storage /* in case data is packed, padding is required */
{
    alignas(atomic_storage_traits<t>::size) t data;
    u8 padding[atomic_storage_traits<t>::padding];
};

template <typename t>
struct atomic_storage<t, false>
{
    alignas(atomic_storage_traits<t>::size) t data;
};

} // namespace rex::impl