#pragma once

#include "rex/types.hpp"
#include "rex/atomic/atomic_operations.hpp"
#include "rex/traits/is_integral.hpp"
#include "rex/traits/is_constructible.hpp"
#include "rex/traits/is_assignable.hpp"
#include "rex/traits/is_same.hpp"
#include "rex/traits/is_trivial.hpp"
#include "rex/traits/is_const_volatile.hpp"

namespace rex
{

// forward decls

template <typename t>
class atomic;

} // namespace rex

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

    static_assert(size <= 16 && size > 0, "Atomic operations are not supported if sizeof(t) > 16 or if sizeof(t) == 0.");
}; // clang-format on

template <typename t, bool padded = (atomic_storage_traits<t>::padding > 0)>
struct atomic_storage /* in case data is packed, padding is required */
{
    constexpr atomic_storage() noexcept = default;
    constexpr atomic_storage(t data) noexcept : data{data} {}

    alignas(atomic_storage_traits<t>::size) t data;
    u8 padding[atomic_storage_traits<t>::padding] = {};
};

template <typename t>
struct atomic_storage<t, false>
{
    alignas(atomic_storage_traits<t>::size) t data;
};

//

template <typename t, bool = is_integral_v<t>>
class atomic_base
{
  public:
    using value_type = t;
    using store_type = atomic_storage<t>;
    using operations = atomic_operations<value_type>;
    using this_type  = atomic_base<t>;

  public:
    atomic_base() noexcept = default;

    constexpr atomic_base(value_type desired) noexcept : m_storage{desired} {}

  public: /* DELETED */
    atomic_base(const this_type &)                   = delete;
    this_type &operator=(const this_type &)          = delete;
    this_type &operator=(const this_type &) volatile = delete;

  public: /* METHODS */
    value_type fetch_add(value_type value, memory_order order = memory_order_seq_cst) noexcept
    {
        return operations::fetch_add(m_storage.data, value, order);
    }
    value_type fetch_add(value_type value, memory_order order = memory_order_seq_cst) volatile noexcept
    {
        return operations::fetch_add(m_storage.data, value, order);
    }

    value_type fetch_sub(value_type value, memory_order order = memory_order_seq_cst) noexcept
    {
        return operations::fetch_sub(m_storage.data, value, order);
    }
    value_type fetch_sub(value_type value, memory_order order = memory_order_seq_cst) volatile noexcept
    {
        return operations::fetch_sub(m_storage.data, value, order);
    }

    value_type fetch_and(value_type value, memory_order order = memory_order_seq_cst) noexcept
    {
        return operations::fetch_and(m_storage.data, value, order);
    }
    value_type fetch_and(value_type value, memory_order order = memory_order_seq_cst) volatile noexcept
    {
        return operations::fetch_and(m_storage.data, value, order);
    }

    value_type fetch_or(value_type value, memory_order order = memory_order_seq_cst) noexcept
    {
        return operations::fetch_or(m_storage.data, value, order);
    }
    value_type fetch_or(value_type value, memory_order order = memory_order_seq_cst) volatile noexcept
    {
        return operations::fetch_or(m_storage.data, value, order);
    }

    value_type fetch_xor(value_type value, memory_order order = memory_order_seq_cst) noexcept
    {
        return operations::fetch_xor(m_storage.data, value, order);
    }
    value_type fetch_xor(value_type value, memory_order order = memory_order_seq_cst) volatile noexcept
    {
        return operations::fetch_xor(m_storage.data, value, order);
    }

    // clang-format off

  public: /* OPERATORS */
    value_type operator++()             noexcept { return fetch_add(1) + 1; }
    value_type operator++()    volatile noexcept { return fetch_add(1) + 1; }
    value_type operator++(int)          noexcept { return fetch_add(1) + 1; }
    value_type operator++(int) volatile noexcept { return fetch_add(1) + 1; }
    value_type operator--()             noexcept { return fetch_sub(1) - 1; }
    value_type operator--()    volatile noexcept { return fetch_sub(1) - 1; }
    value_type operator--(int)          noexcept { return fetch_sub(1) - 1; }
    value_type operator--(int) volatile noexcept { return fetch_sub(1) - 1; }
    value_type operator+=(value_type value)          noexcept { return fetch_add(value) + value; }
    value_type operator+=(value_type value) volatile noexcept { return fetch_add(value) + value; }
    value_type operator-=(value_type value)          noexcept { return fetch_sub(value) - value; }
    value_type operator-=(value_type value) volatile noexcept { return fetch_sub(value) - value; }
    value_type operator&=(value_type value)          noexcept { return fetch_and(value) & value; }
    value_type operator&=(value_type value) volatile noexcept { return fetch_and(value) & value; }
    value_type operator|=(value_type value)          noexcept { return fetch_or (value) | value; }
    value_type operator|=(value_type value) volatile noexcept { return fetch_or (value) | value; }
    value_type operator^=(value_type value)          noexcept { return fetch_xor(value) ^ value; }
    value_type operator^=(value_type value) volatile noexcept { return fetch_xor(value) ^ value; }

    // clang-format on

  private: /* PROTECTED MEMBERS */
    store_type m_storage;

  public: /* FRIENDS :D */
    friend class atomic<t>;
};

template <typename t>
class atomic_base<t, false>
{
  public:
    using value_type = t;
    using store_type = atomic_storage<t>;
    using this_type  = atomic_base<t>;

  public:
    atomic_base() noexcept = default;

    constexpr atomic_base(value_type desired) noexcept : m_storage{desired} {}

  public: /* DELETED */
    atomic_base(const this_type &)                   = delete;
    this_type &operator=(const this_type &)          = delete;
    this_type &operator=(const this_type &) volatile = delete;

  private: /* PROTECTED MEMBERS */
    store_type m_storage;

  public: /* FRIENDS (: */
    friend class atomic<t>;
};

} // namespace rex::impl

namespace rex
{

template <typename t>
class atomic : public impl::atomic_base<t>
{
  public:
    using value_type = t;
    using store_type = impl::atomic_storage<t>;
    using operations = impl::atomic_operations<store_type>;
    using this_type  = atomic<t>;
    using base_type  = impl::atomic_base<t>;

  public:
    atomic() noexcept = default;

    constexpr atomic(value_type desired) noexcept : base_type{desired} {}

  public: /* DELETED */
    atomic(const this_type &)                        = delete;
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

    void store(value_type desired, memory_order order = memory_order_seq_cst) noexcept
    {
        operations::store(base_type::m_storage, {desired}, order);
    }
    void store(value_type desired, memory_order order = memory_order_seq_cst) volatile noexcept
    {
        operations::store(base_type::m_storage, {desired}, order);
    }

    value_type load(memory_order order = memory_order_seq_cst) const noexcept
    {
        return operations::load(base_type::m_storage, order).data;
    }
    value_type load(memory_order order = memory_order_seq_cst) const volatile noexcept
    {
        return operations::load(base_type::m_storage, order).data;
    }

    value_type exchange(value_type desired, memory_order order = memory_order_seq_cst) noexcept
    {
        return operations::exchange(base_type::m_storage, {desired}, order).data;
    }
    value_type exchange(value_type desired, memory_order order = memory_order_seq_cst) volatile noexcept
    {
        return operations::exchange(base_type::m_storage, {desired}, order).data;
    }

    // clang-format off

    bool compare_exchange_weak(value_type &expected, value_type desired, memory_order success, memory_order failure) noexcept
    {
        auto expRes = store_type{expected};
        auto result = operations::cmpxchg(base_type::m_storage, expRes, {desired}, true, success, failure);
        expected    = expRes.data;
        return result;
    }
    bool compare_exchange_weak(value_type &expected, value_type desired, memory_order success, memory_order failure) volatile noexcept
    {
        auto expRes = store_type{expected};
        auto result = operations::cmpxchg(base_type::m_storage, expRes, {desired}, true, success, failure);
        expected    = expRes.data;
        return result;
    }

    bool compare_exchange_weak(value_type &expected, value_type desired, memory_order order = memory_order_seq_cst) noexcept
    {
        if (order == memory_order_release) return compare_exchange_weak(expected, desired, order, memory_order_relaxed);
        if (order == memory_order_acq_rel) return compare_exchange_weak(expected, desired, order, memory_order_acquire);
        return compare_exchange_weak(expected, desired, order, order);
    }
    bool compare_exchange_weak(value_type &expected, value_type desired, memory_order order = memory_order_seq_cst) volatile noexcept
    {
        if (order == memory_order_release) return compare_exchange_weak(expected, desired, order, memory_order_relaxed);
        if (order == memory_order_acq_rel) return compare_exchange_weak(expected, desired, order, memory_order_acquire);
        return compare_exchange_weak(expected, desired, order, order);
    }

    bool compare_exchange_strong(value_type &expected, value_type desired, memory_order success, memory_order failure) noexcept
    {
        auto expRes = store_type{expected};
        auto result = operations::cmpxchg(base_type::m_storage, expRes, {desired}, false, success, failure);
        expected    = expRes.data;
        return result;
    }
    bool compare_exchange_strong(value_type &expected, value_type desired, memory_order success, memory_order failure) volatile noexcept
    {
        auto expRes = store_type{expected};
        auto result = operations::cmpxchg(base_type::m_storage, expRes, {desired}, false, success, failure);
        expected    = expRes.data;
        return result;
    }

    bool compare_exchange_strong(value_type &expected, value_type desired, memory_order order = memory_order_seq_cst) noexcept
    {
        if (order == memory_order_release) return compare_exchange_weak(expected, desired, order, memory_order_relaxed);
        if (order == memory_order_acq_rel) return compare_exchange_weak(expected, desired, order, memory_order_acquire);
        return compare_exchange_weak(expected, desired, order, order);
    }
    bool compare_exchange_strong(value_type &expected, value_type desired, memory_order order = memory_order_seq_cst) volatile noexcept
    {
        if (order == memory_order_release) return compare_exchange_weak(expected, desired, order, memory_order_relaxed);
        if (order == memory_order_acq_rel) return compare_exchange_weak(expected, desired, order, memory_order_acquire);
        return compare_exchange_weak(expected, desired, order, order);
    }

  public: /* OPERATORS */
    operator value_type() const          noexcept { return load(); }
    operator value_type() const volatile noexcept { return load(); }

    value_type operator=(value_type desired)          noexcept { store(desired); return desired; }
    value_type operator=(value_type desired) volatile noexcept { store(desired); return desired; }

    // clang-format on

  public: /* PUBLIC MEMBERS */
    static constexpr bool is_always_lock_free = impl::atomic_operations_are_always_lock_free<t>();

  public:
    static_assert(is_trivially_copyable_v<t> && is_copy_constructible_v<t> && is_move_constructible_v<t> &&
                      is_copy_assignable_v<t> && is_move_assignable_v<t> && is_same_v<t, remove_cv_t<t>>,
                  "Given type `t` does not satisfy the requirements for atomic<t>.");
};

} // namespace rex