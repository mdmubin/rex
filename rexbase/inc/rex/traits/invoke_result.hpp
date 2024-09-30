#pragma once

#include "rex/traits/enable_if.hpp"
#include "rex/traits/is_base_of.hpp"
#include "rex/traits/is_function.hpp"
#include "rex/traits/is_reference_wrapper.hpp"
#include "rex/traits/is_void.hpp"
#include "rex/utils/declval.hpp"
#include "rex/utils/forward.hpp"

namespace rex::impl {

// HELPERS

template <typename T>
class invoke_helper
{
  public:

    template <typename f, typename... a>
    static auto call(f &&func, a &&...args)
        noexcept(noexcept(forward<f>(func)(forward<a>(args)...))) -> decltype(forward<f>(func)(forward<a>(args)...))
    {
        return forward<f>(func)(forward<a>(args)...);
    }
};

template <typename c, typename m>
class invoke_helper<m c::*> /* specialization for member pointers */
{
  private:

    template <typename t, typename = enable_if_t<is_base_of<c, decay_t<t>>::value>>
    static auto get(t &&obj) noexcept -> decltype(forward<t>(obj))
    {
        return forward<t>(obj);
    }

    template <typename t, typename = enable_if_t<is_reference_wrapper_v< decay_t<t>>>>
    static auto get(t &&obj) noexcept -> decltype(obj.get())
    {
        return obj.get();
    }

    template <typename t, typename = enable_if_t<(!is_base_of_v<c, decay_t<t>> && !is_reference_wrapper_v<decay_t<t>>)>>
    static auto get(t &&obj) noexcept -> decltype(*forward<t>(obj))
    {
        return (*forward<t>(obj));
    }

  public:

    template <typename t, typename... a, typename u, typename = enable_if_t<is_function<u>::value>>
    static auto call(u c::*func, t &&obj, a &&...args)
        noexcept(noexcept((invoke_helper::get(forward<t>(obj)).*func)(forward<a>(args)...)))
            -> decltype((invoke_helper::get(forward<t>(obj)).*func)(forward<a>(args)...))
    {
        return (invoke_helper::get(forward<t>(obj)).*func)(forward<a>(args)...);
    }

    template <typename t>
    static auto call(m c::*data, t &&obj)
        noexcept(noexcept(invoke_helper::get(forward<t>(obj)).*data))
            -> decltype(invoke_helper::get(forward<t>(obj)).*data)
    {
        return invoke_helper::get(forward<t>(obj)).*data;
    }
};

template <typename f, typename... a, typename f_decayed = decay_t<f>>
auto invoke(f &&func, a &&...args)
    noexcept(noexcept(invoke_helper<f_decayed>::call(forward<f>(func), forward<a>(args)...)))
        -> decltype(invoke_helper<f_decayed>::call(forward<f>(func), forward<a>(args)...))
{
    return invoke_helper<f_decayed>::call(forward<f>(func), forward<a>(args)...);
}

// IMPL

template <typename /* always void */, typename, typename...>
struct invoke_result {};

template <typename f, typename... a>
struct invoke_result<void_t<decltype(invoke(declval<f>(), declval<a>()...))>, f, a...>
{
    using type = decltype(invoke(declval<f>(), declval<a>()...));
};

} // namespace rex::impl

namespace rex {

template <typename>                  struct result_of;
template <typename f, typename... a> struct result_of<f(a...)> : impl::invoke_result<void, f, a...> {};
template <typename f, typename... a> struct invoke_result      : impl::invoke_result<void, f, a...> {};

/// @brief An alias to the the type returned by invoking `t`.
template <typename t> using result_of_t = typename result_of<t>::type;
/// @brief An alias to the the type returned by invoking `t` using the arguments `...u`.
template <typename t, typename...u> using invoke_result_t = typename invoke_result<t, u...>::type;

} // namespace rex