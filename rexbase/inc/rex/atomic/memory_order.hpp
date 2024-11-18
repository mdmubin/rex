#pragma once

namespace rex
{

/// @brief Specifies how memory accesses are to be ordered around an atomic operation.
enum memory_order
{
    memory_order_relaxed,
    memory_order_consume,
    memory_order_acquire,
    memory_order_release,
    memory_order_acq_rel,
    memory_order_seq_cst,
};

} // namespace rex