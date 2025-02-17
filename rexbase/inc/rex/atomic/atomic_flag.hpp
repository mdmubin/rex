#pragma once

#include "rex/atomic/atomic_impl.hpp"

namespace rex
{

class atomic_flag
{
  public: /* TYPDEFS */
    using this_type = atomic_flag;

  public: /* CTORS */
    constexpr atomic_flag() noexcept = default;

  public: /* DELETED */
    atomic_flag(const this_type &)                   = delete;
    this_type &operator=(const this_type &)          = delete;
    this_type &operator=(const this_type &) volatile = delete;

  public: /* METHODS */
    void clear(memory_order order = memory_order_seq_cst) noexcept
    {
        m_flag.store(false, order);
    }
    void clear(memory_order order = memory_order_seq_cst) volatile noexcept
    {
        m_flag.store(false, order);
    }

    bool test_and_set(memory_order order = memory_order_seq_cst) noexcept
    {
        return m_flag.exchange(true, order);
    }
    bool test_and_set(memory_order order = memory_order_seq_cst) volatile noexcept
    {
        return m_flag.exchange(true, order);
    }

    bool test(memory_order order = memory_order_seq_cst) const noexcept
    {
        return m_flag.load(order);
    }
    bool test(memory_order order = memory_order_seq_cst) const volatile noexcept
    {
        return m_flag.load(order);
    }

  private: /* MEMBERS */
    atomic<bool> m_flag;
};

} // namespace rex