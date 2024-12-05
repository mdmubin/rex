#pragma once

#include "rex/assert.hpp"
#include "rex/atomic/memory_order.hpp"
#include "rex/config.hpp"
#include "rex/mem/addressof.hpp"
#include "rex/types.hpp"

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
        (order <= rex::memory_order_seq_cst &&              \
         order != rex::memory_order_release &&              \
         order != rex::memory_order_acq_rel),               \
        "Invalid memory order constraint for atomic load."  \
    )
#define REX_VERIFY_ATOMIC_STORE_ORDER(order) REX_VERIFY_MSG( \
    (order <= rex::memory_order_seq_cst &&                   \
     order != rex::memory_order_consume &&                   \
     order != rex::memory_order_acquire &&                   \
     order != rex::memory_order_acq_rel),                    \
     "Invalid memory order constraint for atomic store."     \
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
#define REX_PLACE_ATOMIC_RMW_BARRIER_1(order)                     \
    do {                                                          \
        switch (order) {                                          \
        case memory_order_release:                                \
        case memory_order_acq_rel:                                \
        case memory_order_seq_cst: REX_COMPILER_BARRIER(); break; \
        default: /* no barrier */ break;                          \
        }                                                         \
    } while (0)
#define REX_PLACE_ATOMIC_RMW_BARRIER_2(order)                     \
    do {                                                          \
        switch (order) {                                          \
        case memory_order_consume:                                \
        case memory_order_acquire:                                \
        case memory_order_acq_rel:                                \
        case memory_order_seq_cst: REX_COMPILER_BARRIER(); break; \
        default: /* no barrier */ break;                          \
        }                                                         \
    } while (0)

// clang-format on

namespace rex::impl
{

template <typename t, usz = sizeof(t)>
struct atomic_operations
{ // clang-format off
    static_assert(
        sizeof(t) == 1 || sizeof(t) == 2 || sizeof(t) == 4 || sizeof(t) == 8 || sizeof(t) == 16,
        "Atomic operations are only supported for data that has the width of an integral type. "
        "(i.e. sizeof(t) is 1, 2, 4, 8 or 16 bytes)"
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

    static void store(t &storage, t value, memory_order order)
    {
        REX_VERIFY_ATOMIC_STORE_ORDER(order);
        switch (order)
        {
        case memory_order_relaxed:
            *addressof(reinterpret_cast<volatile u8 &>(storage)) = reinterpret_cast<u8 &>(value);
            break;
        case memory_order_release:
            REX_COMPILER_BARRIER();
            *addressof(reinterpret_cast<volatile u8 &>(storage)) = reinterpret_cast<u8 &>(value);
            break;
        case memory_order_seq_cst:
#if defined(REX_COMPILER_MSVC)
            _InterlockedExchange8(addressof(reinterpret_cast<volatile char &>(storage)),
                                  reinterpret_cast<char &>(value));
            break;
#else
            REX_COMPILER_BARRIER();
            __asm__ __volatile__("xchg %0, %1" : "+q"(value) : "m"(storage));
            break;
#endif
        default:
            REX_UNREACHABLE();
        }
    }

    static t exchange(t &storage, t value, memory_order order)
    {
        REX_VERIFY_MSG(order <= memory_order_seq_cst, "Invalid memory order constraint for atomic exchange.");
#if defined(REX_COMPILER_MSVC)
        // NOTE: MSVC STL doesn't use any barrier, so is it ok if we also omit barriers in our own implementation?
        auto result = _InterlockedExchange8(addressof(reinterpret_cast<volatile char &>(storage)),
                                            reinterpret_cast<char &>(value));
        return reinterpret_cast<t &>(result);
#else
        REX_PLACE_ATOMIC_RMW_BARRIER_1(order);
        __asm__ __volatile__("xchg %0, %1" : "+q"(value) : "m"(storage) : "memory");
        REX_PLACE_ATOMIC_RMW_BARRIER_2(order);
        return value;
#endif
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

    static void store(t &storage, t value, memory_order order)
    {
        REX_VERIFY_ATOMIC_STORE_ORDER(order);
        switch (order)
        {
        case memory_order_relaxed:
            *addressof(reinterpret_cast<volatile u16 &>(storage)) = reinterpret_cast<u16 &>(value);
            break;
        case memory_order_release:
            REX_COMPILER_BARRIER();
            *addressof(reinterpret_cast<volatile u16 &>(storage)) = reinterpret_cast<u16 &>(value);
            break;
        case memory_order_seq_cst:
#if defined(REX_COMPILER_MSVC)
            _InterlockedExchange16(addressof(reinterpret_cast<volatile short &>(storage)),
                                   reinterpret_cast<short &>(value));
            break;
#else
            REX_COMPILER_BARRIER();
            __asm__ __volatile__("xchg %0, %1" : "+r"(value) : "m"(storage));
            break;
#endif
        default:
            REX_UNREACHABLE();
        }
    }

    static t exchange(t &storage, t value, memory_order order)
    {
        REX_VERIFY_MSG(order <= memory_order_seq_cst, "Invalid memory order constraint for atomic exchange.");
#if defined(REX_COMPILER_MSVC)
        auto result = _InterlockedExchange16(addressof(reinterpret_cast<volatile short &>(storage)),
                                             reinterpret_cast<short &>(value));
        return reinterpret_cast<t &>(result);
#else
        REX_PLACE_ATOMIC_RMW_BARRIER_1(order);
        __asm__ __volatile__("xchg %0, %1" : "+r"(value) : "m"(storage) : "memory");
        REX_PLACE_ATOMIC_RMW_BARRIER_2(order);
        return value;
#endif
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

    static void store(t &storage, t value, memory_order order)
    {
        REX_VERIFY_ATOMIC_STORE_ORDER(order);
        switch (order)
        {
        case memory_order_relaxed:
            *addressof(reinterpret_cast<volatile u32 &>(storage)) = reinterpret_cast<u32 &>(value);
            break;
        case memory_order_release:
            REX_COMPILER_BARRIER();
            *addressof(reinterpret_cast<volatile u32 &>(storage)) = reinterpret_cast<u32 &>(value);
            break;
        case memory_order_seq_cst:
#if defined(REX_COMPILER_MSVC)
            _InterlockedExchange(addressof(reinterpret_cast<volatile long &>(storage)),
                                 reinterpret_cast<long &>(value));
            break;
#else
            REX_COMPILER_BARRIER();
            __asm__ __volatile__("xchg %0, %1" : "+r"(value) : "m"(storage));
            break;
#endif
        default:
            REX_UNREACHABLE();
        }
    }

    static t exchange(t &storage, t value, memory_order order)
    {
        REX_VERIFY_MSG(order <= memory_order_seq_cst, "Invalid memory order constraint for atomic exchange.");
#if defined(REX_COMPILER_MSVC)
        auto result = _InterlockedExchange(addressof(reinterpret_cast<volatile long &>(storage)),
                                           reinterpret_cast<long &>(value));
        return reinterpret_cast<t &>(result);
#else
        REX_PLACE_ATOMIC_RMW_BARRIER_1(order);
        __asm__ __volatile__("xchg %0, %1" : "+r"(value) : "m"(storage) : "memory");
        REX_PLACE_ATOMIC_RMW_BARRIER_2(order);
        return value;
#endif
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

    static void store(t &storage, t value, memory_order order)
    {
        REX_VERIFY_ATOMIC_STORE_ORDER(order);
        switch (order)
        {
        case memory_order_relaxed:
            *addressof(reinterpret_cast<volatile u64 &>(storage)) = reinterpret_cast<u64 &>(value);
            break;
        case memory_order_release:
            REX_COMPILER_BARRIER();
            *addressof(reinterpret_cast<volatile u64 &>(storage)) = reinterpret_cast<u64 &>(value);
            break;
        case memory_order_seq_cst:
#if defined(REX_COMPILER_MSVC)
            _InterlockedExchange64(addressof(reinterpret_cast<volatile __int64 &>(storage)),
                                   reinterpret_cast<__int64 &>(value));
            break;
#else
            REX_COMPILER_BARRIER();
            __asm__ __volatile__("xchg %0, %1" : "+r"(value) : "m"(storage));
            break;
#endif
        default:
            REX_UNREACHABLE();
        }
    }

    static t exchange(t &storage, t value, memory_order order)
    {
        REX_VERIFY_MSG(order <= memory_order_seq_cst, "Invalid memory order constraint for atomic exchange.");
#if defined(REX_COMPILER_MSVC)
        auto result = _InterlockedExchange64(addressof(reinterpret_cast<volatile __int64 &>(storage)),
                                             reinterpret_cast<__int64 &>(value));
        return reinterpret_cast<t &>(result);
#else
        REX_PLACE_ATOMIC_RMW_BARRIER_1(order);
        __asm__ __volatile__("xchg %0, %1" : "+r"(value) : "m"(storage) : "memory");
        REX_PLACE_ATOMIC_RMW_BARRIER_2(order);
        return value;
#endif
    }
};

template <typename t>
struct atomic_operations<t, 16>
{
  public:
    static t load(t &storage, memory_order order)
    {
#if defined(REX_COMPILER_MSVC)
        __int64 value[2] = {0, 0};
        (void)_InterlockedCompareExchange128((volatile __int64 *)addressof(storage), 0, 0, value);
        return *reinterpret_cast<t *>(value);
#else
        __int128 value;
        __asm__ __volatile__("movdqa %0, %1" : "=x"(value) : "m"(storage));
        REX_PLACE_ATOMIC_LOAD_BARRIER(order);
        return reinterpret_cast<t &>(value);
#endif
    }

    static void store(t &storage, t value, memory_order order)
    {
        REX_VERIFY_ATOMIC_STORE_ORDER(order);
#if defined(REX_COMPILER_MSVC)
        (void)exchange(storage, value, order);
#else
        switch (order)
        {
        case memory_order_relaxed:
            __asm__ __volatile__("movdqa %0, %1" : "=m"(storage) : "x"(value));
            break;
        case memory_order_release:
            REX_COMPILER_BARRIER();
            __asm__ __volatile__("movdqa %0, %1" : "=m"(storage) : "x"(value));
            break;
        case memory_order_seq_cst:
            (void)exchange(storage, value, order);
            break;
        default:
            REX_UNREACHABLE();
        }
#endif
    }

    static t exchange(t &storage, t value, memory_order order)
    {
        REX_VERIFY_MSG(order <= memory_order_seq_cst, "Invalid memory order constraint for atomic exchange.");
        t previous;
        bool success = false;
        while (!success)
        {
            previous = storage;
            i64 *cmp = reinterpret_cast<i64 *>(addressof(previous));
            i64 *dst = reinterpret_cast<i64 *>(addressof(storage));
            i64 *val = reinterpret_cast<i64 *>(addressof(value));
            REX_PLACE_ATOMIC_RMW_BARRIER_1(order);
            success = cmpxchg(dst, val, cmp);
            REX_PLACE_ATOMIC_RMW_BARRIER_2(order);
        }
        return previous;
    }

  private:
    static bool cmpxchg(i64 *dst, i64 *val, i64 *cmp)
    {
#if defined(REX_COMPILER_MSVC)
        return static_cast<bool>(_InterlockedCompareExchange128(dst, val[1], val[0], cmp));
#else
        bool dstCmpEqual;
        __asm__ __volatile__("lock cmpxchg16b %1"
                             : "=@ccz"(dstCmpEqual), "=m"(*dst), "=a"(cmp[0]), "=d"(cmp[1])
                             : "b"(val[0]), "c"(val[1])
                             : "memory", "cc");
        return dstCmpEqual;
#endif
    }
};

} // namespace rex::impl