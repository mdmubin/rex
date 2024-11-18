#pragma once

#include "rex/assert.hpp"
#include "rex/atomic/memory_order.hpp"
#include "rex/config.hpp"
#include "rex/mem/addressof.hpp"
#include "rex/types.hpp"

//

#if defined(REX_COMPILER_CLANG_CL) || defined(REX_COMPILER_MSVC)
    #include <intrin.h>
    #pragma intrinsic(_ReadWriteBarrier)
    #pragma intrinsic(_InterlockedCompareExchange128)
    #define REX_COMPILER_BARRIER() _ReadWriteBarrier() // deprecated. but what to use instead?
#else
    #define REX_COMPILER_BARRIER() __asm__ __volatile__("" ::: "memory")
#endif

// clang-format off

#define REX_VERIFY_ATOMIC_LOAD_ORDER(order) REX_VERIFY_MSG( \
        (order <= rex::memory_order_seq_cst && order != rex::memory_order_release && order != rex::memory_order_acq_rel),\
        "Invalid memory order constraint for atomic load."\
    )

#define REX_PLACE_ATOMIC_LOAD_BARRIER(order) \
    do { \
        switch (order) { \
        case memory_order_relaxed: /* no barrier */ break; \
        case memory_order_consume: \
        case memory_order_acquire: \
        case memory_order_seq_cst: REX_COMPILER_BARRIER(); break; \
        default: /* other cases are pruned by verify_atomic_load_order */ REX_UNREACHABLE(); break; \
        } \
    } while (0)

// clang-format on

//

namespace rex::impl
{

template <typename t, usz = sizeof(t)>
struct atomic_operations
{ // clang-format off
    static_assert(
        sizeof(t) == 1 || sizeof(t) == 2 || sizeof(t) == 4 || sizeof(t) == 8 || sizeof(t) == 16,
        "Lockfree atomic operations are only supported for data that has the width of an integer. (i.e. sizeof(t) is 1, 2, 4, 8 or 16 bytes)"
    );
}; // clang-format on

template <typename t>
struct atomic_operations<t, 1>
{
    static t load(t &storage, memory_order order)
    {
        REX_VERIFY_ATOMIC_LOAD_ORDER(order);
        u8 value = *addressof(reinterpret_cast<volatile u8 &>(storage));
        REX_PLACE_ATOMIC_LOAD_BARRIER(order);
        return reinterpret_cast<t &>(value);
    }
};

template <typename t>
struct atomic_operations<t, 2>
{
    static t load(t &storage, memory_order order)
    {
        REX_VERIFY_ATOMIC_LOAD_ORDER(order);
        u16 value = *addressof(reinterpret_cast<volatile u16 &>(storage));
        REX_PLACE_ATOMIC_LOAD_BARRIER(order);
        return reinterpret_cast<t &>(value);
    }
};

template <typename t>
struct atomic_operations<t, 4>
{
    static t load(t &storage, memory_order order)
    {
        REX_VERIFY_ATOMIC_LOAD_ORDER(order);
        u32 value = *addressof(reinterpret_cast<volatile u32 &>(storage));
        REX_PLACE_ATOMIC_LOAD_BARRIER(order);
        return reinterpret_cast<t &>(value);
    }
};

template <typename t>
struct atomic_operations<t, 8>
{
    static t load(t &storage, memory_order order)
    {
        REX_VERIFY_ATOMIC_LOAD_ORDER(order);
        u64 value = *addressof(reinterpret_cast<volatile u64 &>(storage));
        REX_PLACE_ATOMIC_LOAD_BARRIER(order);
        return reinterpret_cast<t &>(value);
    }
};

template <typename t>
struct atomic_operations<t, 16>
{
    /// @note On clang/gcc, it is important that `storage` be aligned to 16-bytes.
    static t load(t &storage, memory_order order)
    {
#if defined(REX_COMPILER_MSVC)
        i64 value[2];
        // _mm_load_si128, _mm_load_pd, _mm_load_ps: I tried all these intrinsics. But the intrinsics on MSVC fail to
        // generate the required mov aligned dqword instruction, so we resort to this instead.
        _InterlockedCompareExchange128((volatile long long *)addressof(storage), 0, 0, value);
        // no barrier needed here. _InterlockedCompareExchange128 uses locking for the load.
        return *reinterpret_cast<t *>(value);
#else // clang-format off
        __int128 value;
        // GCC generates the required movdqa instruction but clang fails to do that and generates two load 64-bit
        // instructions instead. So we just write our own inline assembly instead. movdqa instruction is guaranteed to
        // be atomic in x64 platforms according to both AMD and Intel dev manuals.
        __asm__ __volatile__
        (
            "movdqa (%1), %0\n"
            : "=x"(value)
            : "r"(addressof(reinterpret_cast<volatile __int128 &>(storage)))
        );
        REX_PLACE_ATOMIC_LOAD_BARRIER(order);
        return reinterpret_cast<t &>(value);
#endif // clang-format on
    }
};

} // namespace rex::impl