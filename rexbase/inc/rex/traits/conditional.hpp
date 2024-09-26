#pragma once

namespace rex {

template <bool cnd, typename t, typename u> struct conditional              { using type = t; };
template           <typename t, typename u> struct conditional<false, t, u> { using type = u; };

/// @brief An alias to type `t` if `cnd` is true, else an alias to type `u` if `cnd` is false.
template <bool cnd, typename t, typename u> using conditional_t = typename conditional<cnd, t, u>::type;

} // namespace rex