#pragma once

#include "rex/types.hpp"
#include "rex/traits/integral_constant.hpp"
#include "rex/traits/is_const_volatile.hpp"
#include "rex/traits/is_arithmetic.hpp"
#include "rex/traits/is_enum.hpp"
#include "rex/traits/is_integral.hpp"
#include "rex/traits/is_same.hpp"

namespace rex::impl {

template <typename t, bool = is_arithmetic_v<t>> struct is_signed   : bool_constant<(static_cast<t>(0) > static_cast<t>(-1))> {};
template <typename t, bool = is_arithmetic_v<t>> struct is_unsigned : bool_constant<(static_cast<t>(0) < static_cast<t>(-1))> {};
template <typename t> struct is_signed  <t, false> : false_type {};
template <typename t> struct is_unsigned<t, false> : false_type {};

//

template <typename t, bool = !is_enum_v<t> && !(is_integral_v<t> && !is_same_v<t, bool>)> 
struct make_signed {};
template <typename t>
struct make_signed<t, false> {
    template <typename u, usz = sizeof(u)> struct signed_type {};
    template <typename u> struct signed_type<u, 1> { using type = i8;  };
    template <typename u> struct signed_type<u, 2> { using type = i16; };
    template <typename u> struct signed_type<u, 4> { using type = i32; };
    template <typename u> struct signed_type<u, 8> { using type = i64; };
    using type = typename signed_type<t>::type;
};
template <typename t, bool = !is_enum_v<t> && !(is_integral_v<t> && !is_same_v<t, bool>)>
struct make_unsigned {};
template <typename t>
struct make_unsigned<t, false> {
    template <typename u, usz = sizeof(u)> struct unsigned_type {};
    template <typename u> struct unsigned_type<u, 1> { using type = u8;  };
    template <typename u> struct unsigned_type<u, 2> { using type = u16; };
    template <typename u> struct unsigned_type<u, 4> { using type = u32; };
    template <typename u> struct unsigned_type<u, 8> { using type = u64; };
    using type = typename unsigned_type<t>::type;
};

} // namespace rex::impl

namespace rex {

template <typename t> struct is_signed   : impl::is_signed<t>   {};
template <typename t> struct is_unsigned : impl::is_unsigned<t> {};

/// @brief True if `t` is a signed type, else false.
template <typename t> inline constexpr bool is_signed_v = is_signed<t>::value;
/// @brief True if `t` is not a signed type, else false. 
template <typename t> inline constexpr bool is_unsigned_v = is_unsigned<t>::value;

//

template <typename t> struct make_signed {
    using type = match_cv_t<t, typename impl::make_signed<remove_cv_t<t>>::type>;
};
template <typename t> struct make_unsigned {
    using type = match_cv_t<t, typename impl::make_unsigned<remove_cv_t<t>>::type>;
};

/// @brief An alias to a signed integral type if `t` may be converted to such. 
template <typename t> using make_signed_t = typename make_signed<t>::type;
/// @brief An alias to an unsigned integral type if `t` may be converted to such.
template <typename t> using make_unsigned_t = typename make_unsigned<t>::type;

} // namespace rex