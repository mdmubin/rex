#pragma once

#include "rex/assert.hpp"
#include "rex/atomic/memory_order.hpp"
#include "rex/config.hpp"
#include "rex/mem/addressof.hpp"
#include "rex/types.hpp"
#include "rex/traits/enable_if.hpp"
#include "rex/traits/is_integral.hpp"

//

#if !defined(REX_ARCHITECTURE_X64)
    #error Atomic operations are currently implemented only for x64 architectures.
#endif

//

#if defined(REX_COMPILER_CLANG_CL) || defined(REX_COMPILER_MSVC)
    #include <intrin.h>
    #pragma intrinsic(_InterlockedExchange)
    #pragma intrinsic(_InterlockedExchange8)
    #pragma intrinsic(_InterlockedExchange16)
    #pragma intrinsic(_InterlockedExchange64)
    #pragma intrinsic(_InterlockedCompareExchange128)
    #pragma intrinsic(_ReadWriteBarrier)
    #define REX_COMPILER_BARRIER() _ReadWriteBarrier() // deprecated. but what to use instead?
#else
    #define REX_COMPILER_BARRIER() __asm__ __volatile__("" ::: "memory")
#endif

// clang-format off

#define REX_VERIFY_ATOMIC_LOAD_ORDER(order) REX_VERIFY_MSG( \
        (order <= memory_order_seq_cst &&                   \
         order != memory_order_release &&                   \
         order != memory_order_acq_rel),                    \
        "Invalid memory order constraint for atomic load."  \
    )
#define REX_VERIFY_ATOMIC_STORE_ORDER(order) REX_VERIFY_MSG( \
        (order <= memory_order_seq_cst &&                    \
         order != memory_order_consume &&                    \
         order != memory_order_acquire &&                    \
         order != memory_order_acq_rel),                     \
         "Invalid memory order constraint for atomic store." \
    )
#define REX_VERIFY_ATOMIC_CMPXCHG_ORDER(success, failure) REX_VERIFY_MSG( \
        (success <= memory_order_seq_cst &&                               \
         failure <= success &&                                            \
         failure != memory_order_release &&                               \
         failure != memory_order_acq_rel),                                \
         "Invalid memory order constraints for atomic compare exchange."  \
    )
#define REX_PLACE_ATOMIC_LOAD_BARRIER(order)                      \
    do {                                                          \
        switch (order) {                                          \
        case memory_order_consume:                                \
        case memory_order_acquire:                                \
        case memory_order_seq_cst: REX_COMPILER_BARRIER(); break; \
        default: /* release/acq_rel pruned by REX_VERIFY_ATOMIC_LOAD_BARRIER, and no barrier for relax */ break; \
        } \
    } while (0)

// clang-format on

namespace rex::impl
{

template <typename t, usz = sizeof(t)>
struct atomic_operations
{
    static_assert(sizeof(t) == 1 || sizeof(t) == 2 || sizeof(t) == 4 || sizeof(t) == 8 || sizeof(t) == 16,
                  "Atomic operations are only supported if sizeof(t) is 1, 2, 4, 8 or 16 bytes.");
};

template <typename t>
struct atomic_operations<t, 1>
{
    static t load(t &storage, memory_order order) noexcept
    {
        REX_VERIFY_ATOMIC_LOAD_ORDER(order);
#if defined(REX_COMPILER_MSVC) || defined(REX_COMPILER_CLANG_CL)
        u8 value = *addressof(reinterpret_cast<volatile u8 &>(storage));
        REX_PLACE_ATOMIC_LOAD_BARRIER(order);
#else
        u8 value = __atomic_load_n(addressof(reinterpret_cast<volatile u8 &>(storage)), order);
#endif
        return reinterpret_cast<t &>(value);
    }

    static void store(t &storage, t desired, memory_order order) noexcept
    {
        REX_VERIFY_ATOMIC_STORE_ORDER(order);
#if defined(REX_COMPILER_MSVC) || defined(REX_COMPILER_CLANG_CL)
        switch (order)
        {
        case memory_order_relaxed:
            *addressof(reinterpret_cast<volatile uint8_t &>(storage)) = reinterpret_cast<uint8_t &>(desired);
            break;
        case memory_order_release:
            REX_COMPILER_BARRIER();
            *addressof(reinterpret_cast<volatile uint8_t &>(storage)) = reinterpret_cast<uint8_t &>(desired);
            break;
        case memory_order_seq_cst:
            _InterlockedExchange8(addressof(reinterpret_cast<volatile char &>(storage)),
                                  reinterpret_cast<char &>(desired));
            break;
        default:
            __assume(false);
        }
#else // use gcc intrinsics (supported on clang as well)
        __atomic_store_n(addressof(reinterpret_cast<volatile uint8_t &>(storage)), reinterpret_cast<uint8_t &>(desired),
                         order);
#endif
    }

    static t exchange(t &storage, t desired, memory_order order) noexcept
    {
        REX_VERIFY_MSG(order <= memory_order_seq_cst, "Invalid memory order constraint for atomic exchange.");
#if defined(REX_COMPILER_MSVC) || defined(REX_COMPILER_CLANG_CL)
        // NOTE: MSVC STL doesn't use any barrier, so is it ok if we also omit barriers in our own implementation?
        char prev = _InterlockedExchange8(addressof(reinterpret_cast<volatile char &>(storage)),
                                          reinterpret_cast<char &>(desired));
#else
        u8 prev = __atomic_exchange_n(addressof(reinterpret_cast<volatile u8 &>(storage)),
                                      reinterpret_cast<u8 &>(desired), order);
#endif
        return reinterpret_cast<t &>(prev);
    }

    static bool cmpxchg(t &storage, t &expected, t desired, bool weak, memory_order success,
                        memory_order failure) noexcept
    {
        REX_VERIFY_ATOMIC_CMPXCHG_ORDER(success, failure);
#if defined(REX_COMPILER_MSVC) || defined(REX_COMPILER_CLANG_CL)
        REX_UNUSED(weak);    // msvc STL only uses strong cmpxchg.
        REX_UNUSED(success); // orderings not really necessary
        REX_UNUSED(failure);

        char required = *addressof(reinterpret_cast<volatile char &>(expected));
        char previous = _InterlockedCompareExchange8(addressof(reinterpret_cast<volatile char &>(storage)),
                                                     reinterpret_cast<char &>(desired), required);

        if (previous == required)
        {
            return true;
        }

        reinterpret_cast<char &>(expected) = previous;
        return false;
#else
        return __atomic_compare_exchange_n(addressof(reinterpret_cast<volatile u8 &>(storage)),
                                           addressof(reinterpret_cast<u8 &>(expected)), reinterpret_cast<u8 &>(desired),
                                           weak, success, failure);
#endif
    }

    static enable_if_t<is_integral_v<t>, t> fetch_add(t &storage, t value, memory_order order) noexcept
    {
#if defined(REX_COMPILER_MSVC) || defined(REX_COMPILER_CLANG_CL)
        REX_VERIFY_MSG(order <= memory_order_seq_cst,
                       "Invalid memory order constraint for atomic fetch add operation.");
        char result = _InterlockedExchangeAdd8(addressof(reinterpret_cast<volatile char &>(storage)),
                                               reinterpret_cast<char &>(value));
        return reinterpret_cast<t &>(result);
#else
        return __atomic_fetch_add(addressof(reinterpret_cast<volatile t &>(storage)), value, order);
#endif
    }

    static enable_if_t<is_integral_v<t>, t> fetch_sub(t &storage, t value, memory_order order) noexcept
    {
#if defined(REX_COMPILER_MSVC) || defined(REX_COMPILER_CLANG_CL)
        return fetch_add(storage, 0 - value, order);
#else
        return __atomic_fetch_sub(addressof(reinterpret_cast<volatile t &>(storage)), value, order);
#endif
    }

    static enable_if_t<is_integral_v<t>, t> fetch_and(t &storage, t value, memory_order order) noexcept
    {
#if defined(REX_COMPILER_MSVC) || defined(REX_COMPILER_CLANG_CL)
        REX_VERIFY_MSG(order <= memory_order_seq_cst,
                       "Invalid memory order constraint for atomic fetch and operation.");
        char result =
            _InterlockedAnd8(addressof(reinterpret_cast<volatile char &>(storage)), reinterpret_cast<char &>(value));
        return reinterpret_cast<t &>(result);
#else
        return __atomic_fetch_and(addressof(reinterpret_cast<volatile t &>(storage)), value, order);
#endif
    }

    static enable_if_t<is_integral_v<t>, t> fetch_or(t &storage, t value, memory_order order) noexcept
    {
#if defined(REX_COMPILER_MSVC) || defined(REX_COMPILER_CLANG_CL)
        REX_VERIFY_MSG(order <= memory_order_seq_cst, "Invalid memory order constraint for atomic fetch or operation.");
        char result =
            _InterlockedOr8(addressof(reinterpret_cast<volatile char &>(storage)), reinterpret_cast<char &>(value));
        return reinterpret_cast<t &>(result);
#else
        return __atomic_fetch_or(addressof(reinterpret_cast<volatile t &>(storage)), value, order);
#endif
    }

    static enable_if_t<is_integral_v<t>, t> fetch_xor(t &storage, t value, memory_order order) noexcept
    {
#if defined(REX_COMPILER_MSVC) || defined(REX_COMPILER_CLANG_CL)
        REX_VERIFY_MSG(order <= memory_order_seq_cst,
                       "Invalid memory order constraint for atomic fetch xor operation.");
        char result =
            _InterlockedXor8(addressof(reinterpret_cast<volatile char &>(storage)), reinterpret_cast<char &>(value));
        return reinterpret_cast<t &>(result);
#else
        return __atomic_fetch_xor(addressof(reinterpret_cast<volatile t &>(storage)), value, order);
#endif
    }
};

} // namespace rex::impl