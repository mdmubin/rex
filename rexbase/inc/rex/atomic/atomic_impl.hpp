#pragma once

#include "rex/types.hpp"
#include "rex/atomic/atomic_operations.hpp"
#include "rex/traits/is_constructible.hpp"
#include "rex/traits/is_assignable.hpp"
#include "rex/traits/is_same.hpp"
#include "rex/traits/is_trivial.hpp"
#include "rex/traits/is_const_volatile.hpp"

namespace rex
{

// forward decl

template <typename t>
class atomic;

} // namespace rex

namespace rex::impl
{

template <typename t>
struct atomic_storage_traits
{
    static constexpr usz size = sizeof(t) == 1  ? 1
                              : sizeof(t) == 2  ? 2
                              : sizeof(t) <= 4  ? 4
                              : sizeof(t) <= 8  ? 8
                              : sizeof(t) <= 16 ? 16
                              : sizeof(t);
    static constexpr usz padding = size - sizeof(t);

    static_assert(size <= 16 && size > 0, "Atomic operations are not supported if sizeof(t) > 16 or if sizeof(t) == 0.");
};

template <typename t, bool padded = (atomic_storage_traits<t>::padding > 0)>
struct atomic_storage /* in case data is packed, padding is required */
{
    alignas(atomic_storage_traits<t>::size) t data = {};
    u8 padding[atomic_storage_traits<t>::padding]  = {};
};

template <typename t>
struct atomic_storage<t, false>
{
    alignas(atomic_storage_traits<t>::size) t data;
};

//

template <typename t>
class atomic_base
{
  public: /* TYPEDEFS */
    using this_type  = atomic_base<t>;
    using store_type = atomic_storage<t>;
    using operations = atomic_operations<store_type>;

  public: /* CTORS */
    atomic_base() noexcept = default;
    constexpr atomic_base(t desired) noexcept : m_storage{desired} {}

  public: /* DELETED */
    atomic_base(const this_type &)                   = delete;
    this_type &operator=(const this_type &)          = delete;
    this_type &operator=(const this_type &) volatile = delete;

  public: /* METHODS */
    bool is_lock_free() const noexcept
    {
        return impl::atomic_operations_are_lock_free<t>();
    }
    bool is_lock_free() const volatile noexcept
    {
        return impl::atomic_operations_are_lock_free<t>();
    }

    void store(t desired, memory_order order = memory_order_seq_cst) noexcept
    {
        operations::store(m_storage, {desired}, order);
    }
    void store(t desired, memory_order order = memory_order_seq_cst) volatile noexcept
    {
        operations::store(const_cast<this_type *>(this)->m_storage, {desired}, order); // const casting like this is ok
    }

    t load(memory_order order = memory_order_seq_cst) const noexcept
    {
        return operations::load(const_cast<this_type *>(this)->m_storage, order).data;
    }
    t load(memory_order order = memory_order_seq_cst) const volatile noexcept
    {
        return operations::load(const_cast<this_type *>(this)->m_storage, order).data;
    }

    t exchange(t desired, memory_order order = memory_order_seq_cst) noexcept
    {
        return operations::exchange(m_storage, {desired}, order).data;
    }
    t exchange(t desired, memory_order order = memory_order_seq_cst) volatile noexcept
    {
        return operations::exchange(const_cast<this_type *>(this)->m_storage, {desired}, order).data;
    }

    // clang-format off

    bool compare_exchange_weak(t &expected, t desired, memory_order success, memory_order failure) noexcept
    {
        auto expRes = store_type{expected};
        auto result = operations::cmpxchg(m_storage, expRes, {desired}, true, success, failure);
        expected    = expRes.data;
        return result;
    }
    bool compare_exchange_weak(t &expected, t desired, memory_order success, memory_order failure) volatile noexcept
    {
        auto expRes = store_type{expected};
        auto result = operations::cmpxchg(const_cast<this_type*>(this)->m_storage, expRes, {desired}, true, success, failure);
        expected    = expRes.data;
        return result;
    }

    bool compare_exchange_weak(t &expected, t desired, memory_order order = memory_order_seq_cst) noexcept
    {
        if (order == memory_order_release) return compare_exchange_weak(expected, desired, order, memory_order_relaxed);
        if (order == memory_order_acq_rel) return compare_exchange_weak(expected, desired, order, memory_order_acquire);
        return compare_exchange_weak(expected, desired, order, order);
    }
    bool compare_exchange_weak(t &expected, t desired, memory_order order = memory_order_seq_cst) volatile noexcept
    {
        if (order == memory_order_release) return compare_exchange_weak(expected, desired, order, memory_order_relaxed);
        if (order == memory_order_acq_rel) return compare_exchange_weak(expected, desired, order, memory_order_acquire);
        return compare_exchange_weak(expected, desired, order, order);
    }

    bool compare_exchange_strong(t &expected, t desired, memory_order success, memory_order failure) noexcept
    {
        auto expRes = store_type{expected};
        auto result = operations::cmpxchg(m_storage, expRes, {desired}, false, success, failure);
        expected    = expRes.data;
        return result;
    }
    bool compare_exchange_strong(t &expected, t desired, memory_order success, memory_order failure) volatile noexcept
    {
        auto expRes = store_type{expected};
        auto result = operations::cmpxchg(const_cast<this_type*>(this)->m_storage, expRes, {desired}, false, success, failure);
        expected    = expRes.data;
        return result;
    }

    bool compare_exchange_strong(t &expected, t desired, memory_order order = memory_order_seq_cst) noexcept
    {
        if (order == memory_order_release) return compare_exchange_weak(expected, desired, order, memory_order_relaxed);
        if (order == memory_order_acq_rel) return compare_exchange_weak(expected, desired, order, memory_order_acquire);
        return compare_exchange_weak(expected, desired, order, order);
    }
    bool compare_exchange_strong(t &expected, t desired, memory_order order = memory_order_seq_cst) volatile noexcept
    {
        if (order == memory_order_release) return compare_exchange_weak(expected, desired, order, memory_order_relaxed);
        if (order == memory_order_acq_rel) return compare_exchange_weak(expected, desired, order, memory_order_acquire);
        return compare_exchange_weak(expected, desired, order, order);
    }
    // clang-format on

  public: /* PUBLIC MEMBERS */
    static constexpr bool is_always_lock_free = impl::atomic_operations_are_always_lock_free<t>();

  private: /* PRIVATE MEMBERS */
    store_type m_storage;

    friend class atomic<t>; // (we want atomic<t> to be able to access `m_storage`)
};

} // namespace rex::impl

namespace rex
{

template <typename t>
class atomic : public impl::atomic_base<t>
{
  public: /* TYPEDEFS */
    using value_type = t;
    using this_type  = atomic<value_type>;
    using base_type  = impl::atomic_base<value_type>;

  public: /* CTORS */
    atomic() noexcept = default;
    constexpr atomic(value_type desired) noexcept : base_type{desired} {}

  public: /* DELETED */
    atomic(const this_type &)                        = delete;
    this_type &operator=(const this_type &)          = delete;
    this_type &operator=(const this_type &) volatile = delete;
    // clang-format off

  public: /* OPERATORS */
    operator value_type() const          noexcept { return base_type::load(); }
    operator value_type() const volatile noexcept { return base_type::load(); }

    value_type operator=(value_type desired)          noexcept { base_type::store(desired); return desired; }
    value_type operator=(value_type desired) volatile noexcept { base_type::store(desired); return desired; }

  public: /* ASSERTIONS */
    static_assert(
        is_trivially_copyable_v<t> &&
        is_copy_constructible_v<t> &&
        is_move_constructible_v<t> &&
        is_copy_assignable_v<t>    &&
        is_move_assignable_v<t>    &&
        is_same_v<t, remove_cv_t<t>>,
        "Given type `t` does not satisfy the requirements for atomic<t>."
    );
    // clang-format on
};

template <typename t>
class atomic<t *> : public impl::atomic_base<t *>
{
  public: /* TYPEDEFS */
    using value_type      = t;
    using pointer_type    = value_type *;
    using this_type       = atomic<pointer_type>;
    using base_type       = impl::atomic_base<pointer_type>;
    using operations      = impl::atomic_operations<pointer_type>;
    using difference_type = isz;

  public: /* CTORS */
    atomic() noexcept = default;
    constexpr atomic(pointer_type desired) noexcept : base_type{desired} {}

  public: /* DELETED */
    atomic(const this_type &)                        = delete;
    this_type &operator=(const this_type &)          = delete;
    this_type &operator=(const this_type &) volatile = delete;

  public: /* METHODS */
    pointer_type fetch_add(difference_type value, memory_order order = memory_order_seq_cst) noexcept
    {
        return operations::fetch_add(base_type::m_storage.data, value * sizeof(value_type), order);
    }
    pointer_type fetch_add(difference_type value, memory_order order = memory_order_seq_cst) volatile noexcept
    {
        return operations::fetch_add(const_cast<this_type *>(this)->m_storage.data, value * sizeof(value_type), order);
    }

    pointer_type fetch_sub(difference_type value, memory_order order = memory_order_seq_cst) noexcept
    {
        return operations::fetch_sub(base_type::m_storage.data, value * sizeof(value_type), order);
    }
    pointer_type fetch_sub(difference_type value, memory_order order = memory_order_seq_cst) volatile noexcept
    {
        return operations::fetch_sub(const_cast<this_type *>(this)->m_storage.data, value * sizeof(value_type), order);
    }
    // clang-format off

  public: /* OPERATORS */
    operator pointer_type() const          noexcept { return base_type::load(); }
    operator pointer_type() const volatile noexcept { return base_type::load(); }

    pointer_type operator=(pointer_type desired)          noexcept { base_type::store(desired); return desired; }
    pointer_type operator=(pointer_type desired) volatile noexcept { base_type::store(desired); return desired; }

    pointer_type operator++()             noexcept { return base_type::fetch_add(1) + 1; }
    pointer_type operator++()    volatile noexcept { return base_type::fetch_add(1) + 1; }
    pointer_type operator++(int)          noexcept { return base_type::fetch_add(1) + 1; }
    pointer_type operator++(int) volatile noexcept { return base_type::fetch_add(1) + 1; }
    pointer_type operator--()             noexcept { return base_type::fetch_sub(1) - 1; }
    pointer_type operator--()    volatile noexcept { return base_type::fetch_sub(1) - 1; }
    pointer_type operator--(int)          noexcept { return base_type::fetch_sub(1) - 1; }
    pointer_type operator--(int) volatile noexcept { return base_type::fetch_sub(1) - 1; }
    pointer_type operator+=(difference_type value)          noexcept { return base_type::fetch_add(value) + value; }
    pointer_type operator+=(difference_type value) volatile noexcept { return base_type::fetch_add(value) + value; }
    pointer_type operator-=(difference_type value)          noexcept { return base_type::fetch_sub(value) - value; }
    pointer_type operator-=(difference_type value) volatile noexcept { return base_type::fetch_sub(value) - value; }
    // clang-format on
};

#define REX_ATOMIC_INTEGRAL_TYPE(integerType)                                                                          \
    template <>                                                                                                        \
    class atomic<integerType> : public impl::atomic_base<integerType>                                                  \
    {                                                                                                                  \
      public: /* TYPEDEFS */                                                                                           \
        using value_type      = integerType;                                                                           \
        using this_type       = atomic<value_type>;                                                                    \
        using base_type       = impl::atomic_base<value_type>;                                                         \
        using operations      = impl::atomic_operations<value_type>;                                                   \
        using difference_type = value_type;                                                                            \
                                                                                                                       \
      public: /* CTORS */                                                                                              \
        atomic() noexcept = default;                                                                                   \
        constexpr atomic(value_type desired) noexcept : base_type{desired} {}                                          \
                                                                                                                       \
      public: /* DELETED */                                                                                            \
        atomic(const this_type &)                        = delete;                                                     \
        this_type &operator=(const this_type &)          = delete;                                                     \
        this_type &operator=(const this_type &) volatile = delete;                                                     \
                                                                                                                       \
      public: /* METHODS */                                                                                            \
        value_type fetch_add(value_type value, memory_order order = memory_order_seq_cst) noexcept                     \
        {                                                                                                              \
            return operations::fetch_add(base_type::m_storage.data, value, order);                                     \
        }                                                                                                              \
        value_type fetch_add(value_type value, memory_order order = memory_order_seq_cst) volatile noexcept            \
        {                                                                                                              \
            return operations::fetch_add(const_cast<this_type *>(this)->m_storage.data, value, order);                 \
        }                                                                                                              \
                                                                                                                       \
        value_type fetch_sub(value_type value, memory_order order = memory_order_seq_cst) noexcept                     \
        {                                                                                                              \
            return operations::fetch_sub(base_type::m_storage.data, value, order);                                     \
        }                                                                                                              \
        value_type fetch_sub(value_type value, memory_order order = memory_order_seq_cst) volatile noexcept            \
        {                                                                                                              \
            return operations::fetch_sub(const_cast<this_type *>(this)->m_storage.data, value, order);                 \
        }                                                                                                              \
                                                                                                                       \
        value_type fetch_and(value_type value, memory_order order = memory_order_seq_cst) noexcept                     \
        {                                                                                                              \
            return operations::fetch_and(base_type::m_storage.data, value, order);                                     \
        }                                                                                                              \
        value_type fetch_and(value_type value, memory_order order = memory_order_seq_cst) volatile noexcept            \
        {                                                                                                              \
            return operations::fetch_and(const_cast<this_type *>(this)->m_storage.data, value, order);                 \
        }                                                                                                              \
                                                                                                                       \
        value_type fetch_or(value_type value, memory_order order = memory_order_seq_cst) noexcept                      \
        {                                                                                                              \
            return operations::fetch_or(base_type::m_storage.data, value, order);                                      \
        }                                                                                                              \
        value_type fetch_or(value_type value, memory_order order = memory_order_seq_cst) volatile noexcept             \
        {                                                                                                              \
            return operations::fetch_or(const_cast<this_type *>(this)->m_storage.data, value, order);                  \
        }                                                                                                              \
                                                                                                                       \
        value_type fetch_xor(value_type value, memory_order order = memory_order_seq_cst) noexcept                     \
        {                                                                                                              \
            return operations::fetch_xor(base_type::m_storage.data, value, order);                                     \
        }                                                                                                              \
        value_type fetch_xor(value_type value, memory_order order = memory_order_seq_cst) volatile noexcept            \
        {                                                                                                              \
            return operations::fetch_xor(const_cast<this_type *>(this)->m_storage.data, value, order);                 \
        }                                                                                                              \
        /* clang-format off */                                                                                         \
                                                                                                                       \
      public: /* OPERATORS */                                                                                          \
        operator value_type() const          noexcept { return base_type::load(); }                                    \
        operator value_type() const volatile noexcept { return base_type::load(); }                                    \
                                                                                                                       \
        value_type operator=(value_type desired)          noexcept { base_type::store(desired); return desired; }      \
        value_type operator=(value_type desired) volatile noexcept { base_type::store(desired); return desired; }      \
                                                                                                                       \
        value_type operator++()             noexcept { return fetch_add(1) + 1; }                                      \
        value_type operator++()    volatile noexcept { return fetch_add(1) + 1; }                                      \
        value_type operator++(int)          noexcept { return fetch_add(1) + 1; }                                      \
        value_type operator++(int) volatile noexcept { return fetch_add(1) + 1; }                                      \
        value_type operator--()             noexcept { return fetch_sub(1) - 1; }                                      \
        value_type operator--()    volatile noexcept { return fetch_sub(1) - 1; }                                      \
        value_type operator--(int)          noexcept { return fetch_sub(1) - 1; }                                      \
        value_type operator--(int) volatile noexcept { return fetch_sub(1) - 1; }                                      \
                                                                                                                       \
        value_type operator+=(value_type value)          noexcept { return fetch_add(value) + value; }                 \
        value_type operator+=(value_type value) volatile noexcept { return fetch_add(value) + value; }                 \
        value_type operator-=(value_type value)          noexcept { return fetch_sub(value) - value; }                 \
        value_type operator-=(value_type value) volatile noexcept { return fetch_sub(value) - value; }                 \
        value_type operator&=(value_type value)          noexcept { return fetch_and(value) & value; }                 \
        value_type operator&=(value_type value) volatile noexcept { return fetch_and(value) & value; }                 \
        value_type operator|=(value_type value)          noexcept { return fetch_or (value) | value; }                 \
        value_type operator|=(value_type value) volatile noexcept { return fetch_or (value) | value; }                 \
        value_type operator^=(value_type value)          noexcept { return fetch_xor(value) ^ value; }                 \
        value_type operator^=(value_type value) volatile noexcept { return fetch_xor(value) ^ value; }                 \
    }
// clang-format on

REX_ATOMIC_INTEGRAL_TYPE(char);
REX_ATOMIC_INTEGRAL_TYPE(short);
REX_ATOMIC_INTEGRAL_TYPE(int);
REX_ATOMIC_INTEGRAL_TYPE(long);
REX_ATOMIC_INTEGRAL_TYPE(long long);
REX_ATOMIC_INTEGRAL_TYPE(unsigned char);
REX_ATOMIC_INTEGRAL_TYPE(unsigned short);
REX_ATOMIC_INTEGRAL_TYPE(unsigned int);
REX_ATOMIC_INTEGRAL_TYPE(unsigned long);
REX_ATOMIC_INTEGRAL_TYPE(unsigned long long);
REX_ATOMIC_INTEGRAL_TYPE(signed char);
REX_ATOMIC_INTEGRAL_TYPE(char16_t);
REX_ATOMIC_INTEGRAL_TYPE(char32_t);
REX_ATOMIC_INTEGRAL_TYPE(wchar_t);
#if !defined(REX_COMPILER_MSVC)
REX_ATOMIC_INTEGRAL_TYPE(__int128_t);
REX_ATOMIC_INTEGRAL_TYPE(__uint128_t);
#endif

// we don't need this anymore
#undef REX_ATOMIC_INTEGRAL_TYPE

} // namespace rex