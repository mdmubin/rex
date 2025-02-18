#pragma once

#include "rex/assert.hpp"
#include "rex/atomic/memory_order.hpp"
#include "rex/config.hpp"
#include "rex/mem/addressof.hpp"
#include "rex/types.hpp"

//

#if !defined(REX_ARCHITECTURE_X64)
    #error Atomic operations are currently implemented only for x64 architectures.
#endif

//

#if defined(REX_COMPILER_MSVC)
    #include <intrin.h>
    #pragma intrinsic(_InterlockedExchange)
    #pragma intrinsic(_InterlockedExchange8)
    #pragma intrinsic(_InterlockedExchange16)
    #pragma intrinsic(_InterlockedExchange64)
    //
    #pragma intrinsic(_InterlockedCompareExchange)
    #pragma intrinsic(_InterlockedCompareExchange8)
    #pragma intrinsic(_InterlockedCompareExchange16)
    #pragma intrinsic(_InterlockedCompareExchange64)
    #pragma intrinsic(_InterlockedCompareExchange128)
    //
    #pragma intrinsic(_InterlockedExchangeAdd)
    #pragma intrinsic(_InterlockedExchangeAdd8)
    #pragma intrinsic(_InterlockedExchangeAdd16)
    #pragma intrinsic(_InterlockedExchangeAdd64)
    //
    #pragma intrinsic(_InterlockedAnd)
    #pragma intrinsic(_InterlockedAnd8)
    #pragma intrinsic(_InterlockedAnd16)
    #pragma intrinsic(_InterlockedAnd64)
    //
    #pragma intrinsic(_InterlockedOr)
    #pragma intrinsic(_InterlockedOr8)
    #pragma intrinsic(_InterlockedOr16)
    #pragma intrinsic(_InterlockedOr64)
    //
    #pragma intrinsic(_InterlockedXor)
    #pragma intrinsic(_InterlockedXor8)
    #pragma intrinsic(_InterlockedXor16)
    #pragma intrinsic(_InterlockedXor64)
    //
    #pragma intrinsic(_ReadWriteBarrier)
    #define REX_COMPILER_BARRIER() _ReadWriteBarrier() // deprecated. but what to use instead?
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
    /// @brief Perform an atomic load operation on `storage`.
    /// @return The value present within `storage`.
    static t load(t &storage, memory_order order) noexcept
    {
        REX_VERIFY_ATOMIC_LOAD_ORDER(order);
#if defined(REX_COMPILER_MSVC)
        u8 value = *addressof(reinterpret_cast<volatile u8 &>(storage));
        REX_PLACE_ATOMIC_LOAD_BARRIER(order);
#else
        u8 value = __atomic_load_n(addressof(reinterpret_cast<volatile u8 &>(storage)), order);
#endif
        return reinterpret_cast<t &>(value);
    }

    /// @brief Perform an atomic operation on `storage` to store `desired`.
    static void store(t &storage, t desired, memory_order order) noexcept
    {
        REX_VERIFY_ATOMIC_STORE_ORDER(order);
#if defined(REX_COMPILER_MSVC)
        switch (order)
        {
        case memory_order_relaxed:
            *addressof(reinterpret_cast<volatile u8 &>(storage)) = reinterpret_cast<u8 &>(desired);
            break;
        case memory_order_release:
            REX_COMPILER_BARRIER();
            *addressof(reinterpret_cast<volatile u8 &>(storage)) = reinterpret_cast<u8 &>(desired);
            break;
        case memory_order_seq_cst:
            _InterlockedExchange8(addressof(reinterpret_cast<volatile char &>(storage)),
                                  reinterpret_cast<char &>(desired));
            break;
        default:
            REX_UNREACHABLE();
        }
#else
        __atomic_store_n(addressof(reinterpret_cast<volatile u8 &>(storage)), reinterpret_cast<u8 &>(desired), order);
#endif
    }

    /// @brief Perform an atomic exchange operation on `storage` to store `desired` into `storage`.
    /// @return The previous value within `storage`.
    static t exchange(t &storage, t desired, memory_order order) noexcept
    {
        REX_VERIFY_MSG(order <= memory_order_seq_cst, "Invalid memory order constraint for atomic exchange.");
#if defined(REX_COMPILER_MSVC)
        // NOTE: MSVC STL doesn't use any barrier, so is it ok if we also omit barriers in our own implementation?
        char prev = _InterlockedExchange8(addressof(reinterpret_cast<volatile char &>(storage)),
                                          reinterpret_cast<char &>(desired));
#else
        u8 prev = __atomic_exchange_n(addressof(reinterpret_cast<volatile u8 &>(storage)),
                                      reinterpret_cast<u8 &>(desired), order);
#endif
        return reinterpret_cast<t &>(prev);
    }

    /// @brief Perform an atomic cmpxchg operation on `storage`. If `storage` is equal to `expected`, the `storage` is
    /// overwritten with the contents of `desired`. Otherwise, the contents of `expected` is overwritten with the
    /// contents of `storage`.
    /// i.e. `if (storage == expected) { storage := desired } else { expected := storage }`
    /// @return Whether `storage` is equal to `expected`.
    static bool cmpxchg(t &storage, t &expected, t desired, bool weak, memory_order success,
                        memory_order failure) noexcept
    {
        REX_VERIFY_ATOMIC_CMPXCHG_ORDER(success, failure);
#if defined(REX_COMPILER_MSVC)
        REX_UNUSED(weak); // msvc STL only uses strong cmpxchg.

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

    /// @brief Update `storage` by adding `value` to it. `storage` is expected to be an integral type.
    /// @return The previous value of `storage`.
    static t fetch_add(t &storage, t value, memory_order order) noexcept
    {
        REX_VERIFY_MSG(order <= memory_order_seq_cst,
                       "Invalid memory order constraint for atomic fetch add operation.");
#if defined(REX_COMPILER_MSVC)
        char result = _InterlockedExchangeAdd8(addressof(reinterpret_cast<volatile char &>(storage)),
                                               reinterpret_cast<char &>(value));
        return reinterpret_cast<t &>(result);
#else
        return __atomic_fetch_add(addressof(reinterpret_cast<volatile t &>(storage)), value, order);
#endif
    }

    /// @brief Update `storage` by subtracting `value` from it. `storage` is expected to be an integral type.
    /// @return The previous value of `storage`.
    static t fetch_sub(t &storage, t value, memory_order order) noexcept
    {
#if defined(REX_COMPILER_MSVC)
        return fetch_add(storage, 0 - value, order);
#else
        REX_VERIFY_MSG(order <= memory_order_seq_cst,
                       "Invalid memory order constraint for atomic fetch sub operation.");
        return __atomic_fetch_sub(addressof(reinterpret_cast<volatile t &>(storage)), value, order);
#endif
    }

    /// @brief Update `storage` by bitwise and-ing `value` with it. `storage` is expected to be an integral type.
    /// @return The previous value of `storage`.
    static t fetch_and(t &storage, t value, memory_order order) noexcept
    {
        REX_VERIFY_MSG(order <= memory_order_seq_cst,
                       "Invalid memory order constraint for atomic fetch and operation.");
#if defined(REX_COMPILER_MSVC)
        char result =
            _InterlockedAnd8(addressof(reinterpret_cast<volatile char &>(storage)), reinterpret_cast<char &>(value));
        return reinterpret_cast<t &>(result);
#else
        return __atomic_fetch_and(addressof(reinterpret_cast<volatile t &>(storage)), value, order);
#endif
    }

    /// @brief Update `storage` by bitwise or-ing `value` with it. `storage` is expected to be an integral type.
    /// @return The previous value of `storage`.
    static t fetch_or(t &storage, t value, memory_order order) noexcept
    {
        REX_VERIFY_MSG(order <= memory_order_seq_cst, "Invalid memory order constraint for atomic fetch or operation.");
#if defined(REX_COMPILER_MSVC)
        char result =
            _InterlockedOr8(addressof(reinterpret_cast<volatile char &>(storage)), reinterpret_cast<char &>(value));
        return reinterpret_cast<t &>(result);
#else
        return __atomic_fetch_or(addressof(reinterpret_cast<volatile t &>(storage)), value, order);
#endif
    }

    /// @brief Update `storage` by bitwise xor-ing `value` with it. `storage` is expected to be an integral type.
    /// @return The previous value of `storage`.
    static t fetch_xor(t &storage, t value, memory_order order) noexcept
    {
        REX_VERIFY_MSG(order <= memory_order_seq_cst,
                       "Invalid memory order constraint for atomic fetch xor operation.");
#if defined(REX_COMPILER_MSVC)
        char result =
            _InterlockedXor8(addressof(reinterpret_cast<volatile char &>(storage)), reinterpret_cast<char &>(value));
        return reinterpret_cast<t &>(result);
#else
        return __atomic_fetch_xor(addressof(reinterpret_cast<volatile t &>(storage)), value, order);
#endif
    }
};

template <typename t>
struct atomic_operations<t, 2>
{
    static t load(t &storage, memory_order order) noexcept
    {
        REX_VERIFY_ATOMIC_LOAD_ORDER(order);
#if defined(REX_COMPILER_MSVC)
        u16 value = *addressof(reinterpret_cast<volatile u16 &>(storage));
        REX_PLACE_ATOMIC_LOAD_BARRIER(order);
#else
        u16 value = __atomic_load_n(addressof(reinterpret_cast<volatile u16 &>(storage)), order);
#endif
        return reinterpret_cast<t &>(value);
    }

    static void store(t &storage, t desired, memory_order order) noexcept
    {
        REX_VERIFY_ATOMIC_STORE_ORDER(order);
#if defined(REX_COMPILER_MSVC)
        switch (order)
        {
        case memory_order_relaxed:
            *addressof(reinterpret_cast<volatile u16 &>(storage)) = reinterpret_cast<u16 &>(desired);
            break;
        case memory_order_release:
            REX_COMPILER_BARRIER();
            *addressof(reinterpret_cast<volatile u16 &>(storage)) = reinterpret_cast<u16 &>(desired);
            break;
        case memory_order_seq_cst:
            _InterlockedExchange16(addressof(reinterpret_cast<volatile short &>(storage)),
                                   reinterpret_cast<short &>(desired));
            break;
        default:
            REX_UNREACHABLE();
        }
#else
        __atomic_store_n(addressof(reinterpret_cast<volatile u16 &>(storage)), reinterpret_cast<u16 &>(desired), order);
#endif
    }

    static t exchange(t &storage, t desired, memory_order order) noexcept
    {
        REX_VERIFY_MSG(order <= memory_order_seq_cst, "Invalid memory order constraint for atomic exchange.");
#if defined(REX_COMPILER_MSVC)
        short prev = _InterlockedExchange16(addressof(reinterpret_cast<volatile short &>(storage)),
                                            reinterpret_cast<short &>(desired));
#else
        u16 prev = __atomic_exchange_n(addressof(reinterpret_cast<volatile u16 &>(storage)),
                                       reinterpret_cast<u16 &>(desired), order);
#endif
        return reinterpret_cast<t &>(prev);
    }

    static bool cmpxchg(t &storage, t &expected, t desired, bool weak, memory_order success,
                        memory_order failure) noexcept
    {
        REX_VERIFY_ATOMIC_CMPXCHG_ORDER(success, failure);
#if defined(REX_COMPILER_MSVC)
        REX_UNUSED(weak); // msvc STL only uses strong cmpxchg.

        short required = *addressof(reinterpret_cast<volatile short &>(expected));
        short previous = _InterlockedCompareExchange16(addressof(reinterpret_cast<volatile short &>(storage)),
                                                       reinterpret_cast<short &>(desired), required);

        if (previous == required)
        {
            return true;
        }

        reinterpret_cast<short &>(expected) = previous;
        return false;
#else
        return __atomic_compare_exchange_n(addressof(reinterpret_cast<volatile u16 &>(storage)),
                                           addressof(reinterpret_cast<u16 &>(expected)),
                                           reinterpret_cast<u16 &>(desired), weak, success, failure);
#endif
    }

    static t fetch_add(t &storage, t value, memory_order order) noexcept
    {
        REX_VERIFY_MSG(order <= memory_order_seq_cst,
                       "Invalid memory order constraint for atomic fetch add operation.");
#if defined(REX_COMPILER_MSVC)
        short result = _InterlockedExchangeAdd16(addressof(reinterpret_cast<volatile short &>(storage)),
                                                 reinterpret_cast<short &>(value));
        return reinterpret_cast<t &>(result);
#else
        return __atomic_fetch_add(addressof(reinterpret_cast<volatile t &>(storage)), value, order);
#endif
    }

    static t fetch_sub(t &storage, t value, memory_order order) noexcept
    {
#if defined(REX_COMPILER_MSVC)
        return fetch_add(storage, 0 - value, order);
#else
        REX_VERIFY_MSG(order <= memory_order_seq_cst,
                       "Invalid memory order constraint for atomic fetch sub operation.");
        return __atomic_fetch_sub(addressof(reinterpret_cast<volatile t &>(storage)), value, order);
#endif
    }

    static t fetch_and(t &storage, t value, memory_order order) noexcept
    {
        REX_VERIFY_MSG(order <= memory_order_seq_cst,
                       "Invalid memory order constraint for atomic fetch and operation.");
#if defined(REX_COMPILER_MSVC)
        short result =
            _InterlockedAnd16(addressof(reinterpret_cast<volatile short &>(storage)), reinterpret_cast<short &>(value));
        return reinterpret_cast<t &>(result);
#else
        return __atomic_fetch_and(addressof(reinterpret_cast<volatile t &>(storage)), value, order);
#endif
    }

    static t fetch_or(t &storage, t value, memory_order order) noexcept
    {
        REX_VERIFY_MSG(order <= memory_order_seq_cst, "Invalid memory order constraint for atomic fetch or operation.");
#if defined(REX_COMPILER_MSVC)
        short result =
            _InterlockedOr16(addressof(reinterpret_cast<volatile short &>(storage)), reinterpret_cast<short &>(value));
        return reinterpret_cast<t &>(result);
#else
        return __atomic_fetch_or(addressof(reinterpret_cast<volatile t &>(storage)), value, order);
#endif
    }

    static t fetch_xor(t &storage, t value, memory_order order) noexcept
    {
        REX_VERIFY_MSG(order <= memory_order_seq_cst,
                       "Invalid memory order constraint for atomic fetch xor operation.");
#if defined(REX_COMPILER_MSVC)
        short result =
            _InterlockedXor16(addressof(reinterpret_cast<volatile short &>(storage)), reinterpret_cast<short &>(value));
        return reinterpret_cast<t &>(result);
#else
        return __atomic_fetch_xor(addressof(reinterpret_cast<volatile t &>(storage)), value, order);
#endif
    }
};

template <typename t>
struct atomic_operations<t, 4>
{
    static t load(t &storage, memory_order order) noexcept
    {
        REX_VERIFY_ATOMIC_LOAD_ORDER(order);
#if defined(REX_COMPILER_MSVC)
        u32 value = *addressof(reinterpret_cast<volatile u32 &>(storage));
        REX_PLACE_ATOMIC_LOAD_BARRIER(order);
#else
        u32 value = __atomic_load_n(addressof(reinterpret_cast<volatile u32 &>(storage)), order);
#endif
        return reinterpret_cast<t &>(value);
    }

    static void store(t &storage, t desired, memory_order order) noexcept
    {
        REX_VERIFY_ATOMIC_STORE_ORDER(order);
#if defined(REX_COMPILER_MSVC)
        switch (order)
        {
        case memory_order_relaxed:
            *addressof(reinterpret_cast<volatile u32 &>(storage)) = reinterpret_cast<u32 &>(desired);
            break;
        case memory_order_release:
            REX_COMPILER_BARRIER();
            *addressof(reinterpret_cast<volatile u32 &>(storage)) = reinterpret_cast<u32 &>(desired);
            break;
        case memory_order_seq_cst:
            _InterlockedExchange(addressof(reinterpret_cast<volatile long &>(storage)),
                                 reinterpret_cast<long &>(desired));
            break;
        default:
            REX_UNREACHABLE();
        }
#else
        __atomic_store_n(addressof(reinterpret_cast<volatile u32 &>(storage)), reinterpret_cast<u32 &>(desired), order);
#endif
    }

    static t exchange(t &storage, t desired, memory_order order) noexcept
    {
        REX_VERIFY_MSG(order <= memory_order_seq_cst, "Invalid memory order constraint for atomic exchange.");
#if defined(REX_COMPILER_MSVC)
        long prev = _InterlockedExchange(addressof(reinterpret_cast<volatile long &>(storage)),
                                         reinterpret_cast<long &>(desired));
#else
        u32 prev = __atomic_exchange_n(addressof(reinterpret_cast<volatile u32 &>(storage)),
                                       reinterpret_cast<u32 &>(desired), order);
#endif
        return reinterpret_cast<t &>(prev);
    }

    static bool cmpxchg(t &storage, t &expected, t desired, bool weak, memory_order success,
                        memory_order failure) noexcept
    {
        REX_VERIFY_ATOMIC_CMPXCHG_ORDER(success, failure);
#if defined(REX_COMPILER_MSVC)
        REX_UNUSED(weak); // msvc STL only uses strong cmpxchg.

        long required = *addressof(reinterpret_cast<volatile long &>(expected));
        long previous = _InterlockedCompareExchange(addressof(reinterpret_cast<volatile long &>(storage)),
                                                    reinterpret_cast<long &>(desired), required);

        if (previous == required)
        {
            return true;
        }

        reinterpret_cast<long &>(expected) = previous;
        return false;
#else
        return __atomic_compare_exchange_n(addressof(reinterpret_cast<volatile u32 &>(storage)),
                                           addressof(reinterpret_cast<u32 &>(expected)),
                                           reinterpret_cast<u32 &>(desired), weak, success, failure);
#endif
    }

    static t fetch_add(t &storage, t value, memory_order order) noexcept
    {
        REX_VERIFY_MSG(order <= memory_order_seq_cst,
                       "Invalid memory order constraint for atomic fetch add operation.");
#if defined(REX_COMPILER_MSVC)
        long result = _InterlockedExchangeAdd(addressof(reinterpret_cast<volatile long &>(storage)),
                                              reinterpret_cast<long &>(value));
        return reinterpret_cast<t &>(result);
#else
        return __atomic_fetch_add(addressof(reinterpret_cast<volatile t &>(storage)), value, order);
#endif
    }

    static t fetch_sub(t &storage, t value, memory_order order) noexcept
    {
#if defined(REX_COMPILER_MSVC)
        return fetch_add(storage, 0 - value, order);
#else
        REX_VERIFY_MSG(order <= memory_order_seq_cst,
                       "Invalid memory order constraint for atomic fetch sub operation.");
        return __atomic_fetch_sub(addressof(reinterpret_cast<volatile t &>(storage)), value, order);
#endif
    }

    static t fetch_and(t &storage, t value, memory_order order) noexcept
    {
        REX_VERIFY_MSG(order <= memory_order_seq_cst,
                       "Invalid memory order constraint for atomic fetch and operation.");
#if defined(REX_COMPILER_MSVC)
        long result =
            _InterlockedAnd(addressof(reinterpret_cast<volatile long &>(storage)), reinterpret_cast<long &>(value));
        return reinterpret_cast<t &>(result);
#else
        return __atomic_fetch_and(addressof(reinterpret_cast<volatile t &>(storage)), value, order);
#endif
    }

    static t fetch_or(t &storage, t value, memory_order order) noexcept
    {
        REX_VERIFY_MSG(order <= memory_order_seq_cst, "Invalid memory order constraint for atomic fetch or operation.");
#if defined(REX_COMPILER_MSVC)
        long result =
            _InterlockedOr(addressof(reinterpret_cast<volatile long &>(storage)), reinterpret_cast<long &>(value));
        return reinterpret_cast<t &>(result);
#else
        return __atomic_fetch_or(addressof(reinterpret_cast<volatile t &>(storage)), value, order);
#endif
    }

    static t fetch_xor(t &storage, t value, memory_order order) noexcept
    {
        REX_VERIFY_MSG(order <= memory_order_seq_cst,
                       "Invalid memory order constraint for atomic fetch xor operation.");
#if defined(REX_COMPILER_MSVC)
        long result =
            _InterlockedXor(addressof(reinterpret_cast<volatile long &>(storage)), reinterpret_cast<long &>(value));
        return reinterpret_cast<t &>(result);
#else
        return __atomic_fetch_xor(addressof(reinterpret_cast<volatile t &>(storage)), value, order);
#endif
    }
};

template <typename t>
struct atomic_operations<t, 8>
{
    static t load(t &storage, memory_order order) noexcept
    {
        REX_VERIFY_ATOMIC_LOAD_ORDER(order);
#if defined(REX_COMPILER_MSVC)
        u64 value = *addressof(reinterpret_cast<volatile u64 &>(storage));
        REX_PLACE_ATOMIC_LOAD_BARRIER(order);
#else
        u64 value = __atomic_load_n(addressof(reinterpret_cast<volatile u64 &>(storage)), order);
#endif
        return reinterpret_cast<t &>(value);
    }

    static void store(t &storage, t desired, memory_order order) noexcept
    {
        REX_VERIFY_ATOMIC_STORE_ORDER(order);
#if defined(REX_COMPILER_MSVC)
        switch (order)
        {
        case memory_order_relaxed:
            *addressof(reinterpret_cast<volatile u64 &>(storage)) = reinterpret_cast<u64 &>(desired);
            break;
        case memory_order_release:
            REX_COMPILER_BARRIER();
            *addressof(reinterpret_cast<volatile u64 &>(storage)) = reinterpret_cast<u64 &>(desired);
            break;
        case memory_order_seq_cst:
            _InterlockedExchange64(addressof(reinterpret_cast<volatile __int64 &>(storage)),
                                   reinterpret_cast<__int64 &>(desired));
            break;
        default:
            REX_UNREACHABLE();
        }
#else
        __atomic_store_n(addressof(reinterpret_cast<volatile u64 &>(storage)), reinterpret_cast<u64 &>(desired), order);
#endif
    }

    static t exchange(t &storage, t desired, memory_order order) noexcept
    {
        REX_VERIFY_MSG(order <= memory_order_seq_cst, "Invalid memory order constraint for atomic exchange.");
#if defined(REX_COMPILER_MSVC)
        __int64 prev = _InterlockedExchange64(addressof(reinterpret_cast<volatile __int64 &>(storage)),
                                              reinterpret_cast<__int64 &>(desired));
#else
        u64 prev = __atomic_exchange_n(addressof(reinterpret_cast<volatile u64 &>(storage)),
                                       reinterpret_cast<u64 &>(desired), order);
#endif
        return reinterpret_cast<t &>(prev);
    }

    static bool cmpxchg(t &storage, t &expected, t desired, bool weak, memory_order success,
                        memory_order failure) noexcept
    {
        REX_VERIFY_ATOMIC_CMPXCHG_ORDER(success, failure);
#if defined(REX_COMPILER_MSVC)
        REX_UNUSED(weak); // msvc STL only uses strong cmpxchg.

        __int64 required = *addressof(reinterpret_cast<volatile __int64 &>(expected));
        __int64 previous = _InterlockedCompareExchange64(addressof(reinterpret_cast<volatile __int64 &>(storage)),
                                                         reinterpret_cast<__int64 &>(desired), required);

        if (previous == required)
        {
            return true;
        }

        reinterpret_cast<__int64 &>(expected) = previous;
        return false;
#else
        return __atomic_compare_exchange_n(addressof(reinterpret_cast<volatile u64 &>(storage)),
                                           addressof(reinterpret_cast<u64 &>(expected)),
                                           reinterpret_cast<u64 &>(desired), weak, success, failure);
#endif
    }

    static t fetch_add(t &storage, t value, memory_order order) noexcept
    {
        REX_VERIFY_MSG(order <= memory_order_seq_cst,
                       "Invalid memory order constraint for atomic fetch add operation.");
#if defined(REX_COMPILER_MSVC)
        __int64 result = _InterlockedExchangeAdd64(addressof(reinterpret_cast<volatile __int64 &>(storage)),
                                                   reinterpret_cast<__int64 &>(value));
        return reinterpret_cast<t &>(result);
#else
        return __atomic_fetch_add(addressof(reinterpret_cast<volatile t &>(storage)), value, order);
#endif
    }

    static t fetch_sub(t &storage, t value, memory_order order) noexcept
    {
#if defined(REX_COMPILER_MSVC)
        return fetch_add(storage, 0 - value, order);
#else
        REX_VERIFY_MSG(order <= memory_order_seq_cst,
                       "Invalid memory order constraint for atomic fetch sub operation.");
        return __atomic_fetch_sub(addressof(reinterpret_cast<volatile t &>(storage)), value, order);
#endif
    }

    static t fetch_and(t &storage, t value, memory_order order) noexcept
    {
        REX_VERIFY_MSG(order <= memory_order_seq_cst,
                       "Invalid memory order constraint for atomic fetch and operation.");
#if defined(REX_COMPILER_MSVC)
        __int64 result = _InterlockedAnd64(addressof(reinterpret_cast<volatile __int64 &>(storage)),
                                           reinterpret_cast<__int64 &>(value));
        return reinterpret_cast<t &>(result);
#else
        return __atomic_fetch_and(addressof(reinterpret_cast<volatile t &>(storage)), value, order);
#endif
    }

    static t fetch_or(t &storage, t value, memory_order order) noexcept
    {
        REX_VERIFY_MSG(order <= memory_order_seq_cst, "Invalid memory order constraint for atomic fetch or operation.");
#if defined(REX_COMPILER_MSVC)
        __int64 result = _InterlockedOr64(addressof(reinterpret_cast<volatile __int64 &>(storage)),
                                          reinterpret_cast<__int64 &>(value));
        return reinterpret_cast<t &>(result);
#else
        return __atomic_fetch_or(addressof(reinterpret_cast<volatile t &>(storage)), value, order);
#endif
    }

    static t fetch_xor(t &storage, t value, memory_order order) noexcept
    {
        REX_VERIFY_MSG(order <= memory_order_seq_cst,
                       "Invalid memory order constraint for atomic fetch xor operation.");
#if defined(REX_COMPILER_MSVC)
        __int64 result = _InterlockedXor64(addressof(reinterpret_cast<volatile __int64 &>(storage)),
                                           reinterpret_cast<__int64 &>(value));
        return reinterpret_cast<t &>(result);
#else
        return __atomic_fetch_xor(addressof(reinterpret_cast<volatile t &>(storage)), value, order);
#endif
    }
};

template <typename t>
struct atomic_operations<t, 16>
{
    static t load(t &storage, memory_order order) noexcept
    {
        REX_VERIFY_ATOMIC_LOAD_ORDER(order);
#if defined(REX_COMPILER_MSVC)
        __int64 value[2] = {0, 0};
        (void)_InterlockedCompareExchange128((volatile __int64 *)addressof(storage), 0, 0, value);
        return *reinterpret_cast<t *>(value);
#else
        __int128 value = __atomic_load_n(addressof(reinterpret_cast<volatile __int128 &>(storage)), order);
        return reinterpret_cast<t &>(value);
#endif
    }

    static void store(t &storage, t desired, memory_order order) noexcept
    {
        REX_VERIFY_ATOMIC_STORE_ORDER(order);
#if defined(REX_COMPILER_MSVC)
        (void)exchange(storage, desired, order);
#else
        __atomic_store_n(addressof(reinterpret_cast<volatile __int128 &>(storage)),
                         reinterpret_cast<__int128 &>(desired), order);
#endif
    }

    static t exchange(t &storage, t desired, memory_order order) noexcept
    {
        REX_VERIFY_MSG(order <= memory_order_seq_cst, "Invalid memory order constraint for atomic exchange.");
#if defined(REX_COMPILER_MSVC)
        // from msvc STL
        t previous = desired;
        while (!cmpxchg(storage, previous, desired))
        {
            // keep trying until previous value and storage are equal
        }
        return previous;
#else
        __int128 prev = __atomic_exchange_n(addressof(reinterpret_cast<volatile __int128 &>(storage)),
                                            reinterpret_cast<__int128 &>(desired), order);
        return reinterpret_cast<t &>(prev);
#endif
    }

    static bool cmpxchg(t &storage, t &expected, t desired, bool weak, memory_order success,
                        memory_order failure) noexcept
    {
        REX_VERIFY_ATOMIC_CMPXCHG_ORDER(success, failure);
#if defined(REX_COMPILER_MSVC)
        REX_UNUSED(weak); // msvc STL only uses strong cmpxchg.

        alignas(16) __int64 storageData[2] = {
            reinterpret_cast<__int64 *>(addressof(storage))[0],
            reinterpret_cast<__int64 *>(addressof(storage))[1],
        };

        auto result = _InterlockedCompareExchange128(
            reinterpret_cast<volatile __int64 *>(addressof(storage)), // - storage as i64 pointer
            reinterpret_cast<__int64 *>(addressof(desired))[1],       // - desired high
            reinterpret_cast<__int64 *>(addressof(desired))[0],       // - desired low
            reinterpret_cast<__int64 *>(addressof(expected))          // - expected data
        );

        if (result)
        {
            return true;
        }

        reinterpret_cast<__int64 *>(addressof(expected))[0] = storageData[0];
        reinterpret_cast<__int64 *>(addressof(expected))[1] = storageData[1];
        return false;
#else
        return __atomic_compare_exchange_n(addressof(reinterpret_cast<volatile __int128 &>(storage)),
                                           addressof(reinterpret_cast<__int128 &>(expected)),
                                           reinterpret_cast<u8 &>(desired), weak, success, failure);
#endif
    }
};

template <typename t>
constexpr bool atomic_operations_are_always_lock_free()
{
#if defined(REX_COMPILER_MSVC)
    return sizeof(t) <= 8 && ((sizeof(t) - 1) & sizeof(t)) == 0;
#else
    return __atomic_always_lock_free(sizeof(t), 0);
#endif
}

template <typename t>
bool atomic_operations_are_lock_free()
{
#if defined(REX_COMPILER_MSVC)
    return atomic_operations_are_always_lock_free<t>();
#else
    return __atomic_is_lock_free(sizeof(t), 0);
#endif
}

} // namespace rex::impl