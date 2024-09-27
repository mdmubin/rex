#pragma once

namespace rex {

template <bool, typename t = void> struct enable_if          {};
template       <typename t>        struct enable_if<true, t> { using type = t; };

/// An alias to the type `t` if the boolean `cnd` is true, else undefined.
template <bool cnd, typename t = void> using enable_if_t = typename enable_if<cnd, t>::type;

} // namespace rex