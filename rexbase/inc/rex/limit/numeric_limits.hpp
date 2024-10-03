#pragma once

#include <limits.h>
#include <float.h>

#include "rex/config.hpp"
#include "rex/limit/float_denorm_style.hpp"
#include "rex/limit/float_round_style.hpp"
#include "rex/traits/is_signed.hpp"
#include "rex/types.hpp"

namespace rex::impl
{ // clang-format off

struct numeric_limits_base
{
    static constexpr bool has_denorm_loss   = false;
    static constexpr bool has_infinity      = false;
    static constexpr bool has_quiet_NaN     = false;
    static constexpr bool has_signaling_NaN = false;
    static constexpr bool is_bounded        = false;
    static constexpr bool is_exact          = false;
    static constexpr bool is_iec559         = false;
    static constexpr bool is_integer        = false;
    static constexpr bool is_modulo         = false;
    static constexpr bool is_signed         = false;
    static constexpr bool is_specialized    = false;
    static constexpr bool tinyness_before   = false;
    static constexpr bool traps             = false;

    static constexpr int digits         = 0;
    static constexpr int digits10       = 0;
    static constexpr int max_digits10   = 0;
    static constexpr int max_exponent   = 0;
    static constexpr int max_exponent10 = 0;
    static constexpr int min_exponent   = 0;
    static constexpr int min_exponent10 = 0;
    static constexpr int radix          = 0;

    static constexpr float_round_style round_style = round_toward_zero;
    static constexpr float_denorm_style has_denorm = denorm_absent;
};

template <typename t, t min_value, t max_value>
struct integral_limits_base : numeric_limits_base
{
    static constexpr bool is_bounded     = true;
    static constexpr bool is_exact       = true;
    static constexpr bool is_integer     = true;
    static constexpr bool is_modulo      = is_unsigned_v<t>;
    static constexpr bool is_signed      = is_signed_v<t>;
    static constexpr bool is_specialized = true;
    static constexpr bool traps          = true;

    static constexpr int digits   = sizeof(t) * 8 - is_signed_v<t>;
    static constexpr int digits10 = digits * 30'103 / 100'000;
    static constexpr int radix    = 2;

    static constexpr t denorm_min()    noexcept { return static_cast<t>(0); }
    static constexpr t epsilon()       noexcept { return static_cast<t>(0); }
    static constexpr t infinity()      noexcept { return static_cast<t>(0); }
    static constexpr t lowest()        noexcept { return min(); }
    static constexpr t min()           noexcept { return min_value; }
    static constexpr t max()           noexcept { return max_value; }
    static constexpr t quiet_NaN()     noexcept { return static_cast<t>(0); }
    static constexpr t round_error()   noexcept { return static_cast<t>(0); }
    static constexpr t signaling_NaN() noexcept { return static_cast<t>(0); }
};

struct float_limits_base : numeric_limits_base
{
    static constexpr bool has_infinity = true;
    static constexpr bool has_quiet_NaN = true;
    static constexpr bool has_signaling_NaN = true;
    static constexpr bool is_bounded = true;
    static constexpr bool is_iec559 = true;
    static constexpr bool is_signed = true;
    static constexpr bool is_specialized = true;

    static constexpr int radix = FLT_RADIX;

    static constexpr float_round_style round_style = round_to_nearest;
    static constexpr float_denorm_style has_denorm = denorm_present;
};

} // namespace rex::impl

namespace rex {

template <typename t>
struct numeric_limits : impl::numeric_limits_base
{
    static constexpr t denorm_min()    noexcept { return t(); }
    static constexpr t epsilon()       noexcept { return t(); }
    static constexpr t infinity()      noexcept { return t(); }
    static constexpr t lowest()        noexcept { return t(); }
    static constexpr t min()           noexcept { return t(); }
    static constexpr t max()           noexcept { return t(); }
    static constexpr t quiet_NaN()     noexcept { return t(); }
    static constexpr t round_error()   noexcept { return t(); }
    static constexpr t signaling_NaN() noexcept { return t(); }
};

template <typename t> struct numeric_limits<const t>          : numeric_limits<t> {};
template <typename t> struct numeric_limits<volatile t>       : numeric_limits<t> {};
template <typename t> struct numeric_limits<const volatile t> : numeric_limits<t> {};

//

template <>
struct numeric_limits<bool> : impl::integral_limits_base<bool, false, true>
{
    static constexpr int digits     = 1;
    static constexpr int digits10   = 0;
    static constexpr bool is_modulo = false;
};

template <> struct numeric_limits<char>               : impl::integral_limits_base<char,               CHAR_MIN,      CHAR_MAX>       {};
template <> struct numeric_limits<signed char>        : impl::integral_limits_base<signed char,        SCHAR_MIN,     SCHAR_MAX>      {};
template <> struct numeric_limits<unsigned char>      : impl::integral_limits_base<unsigned char,      0,             UCHAR_MAX>      {};
template <> struct numeric_limits<short>              : impl::integral_limits_base<short,              SHRT_MIN,      SHRT_MAX>       {};
template <> struct numeric_limits<unsigned short>     : impl::integral_limits_base<unsigned short,     0,             USHRT_MAX>      {};
template <> struct numeric_limits<int>                : impl::integral_limits_base<int,                INT_MIN,       INT_MAX>        {};
template <> struct numeric_limits<unsigned int>       : impl::integral_limits_base<unsigned int,       0,             UINT_MAX>       {};
template <> struct numeric_limits<long>               : impl::integral_limits_base<long,               LONG_MIN,      LONG_MAX>       {};
template <> struct numeric_limits<unsigned long>      : impl::integral_limits_base<unsigned long,      0,             ULONG_MAX>      {};
template <> struct numeric_limits<long long>          : impl::integral_limits_base<long long,          LONG_LONG_MIN, LONG_LONG_MAX>  {};
template <> struct numeric_limits<unsigned long long> : impl::integral_limits_base<unsigned long long, 0,             ULONG_LONG_MAX> {};

//

template <> struct numeric_limits<float> : impl::float_limits_base
{
    static constexpr int digits         = FLT_DIG;
    static constexpr int digits10       = FLT_DIG;
    static constexpr int max_digits10   = FLT_DECIMAL_DIG;
    static constexpr int max_exponent   = FLT_MAX_EXP;
    static constexpr int max_exponent10 = FLT_MAX_10_EXP;
    static constexpr int min_exponent   = FLT_MIN_EXP;
    static constexpr int min_exponent10 = FLT_MIN_10_EXP;

    static constexpr float denorm_min()    noexcept { return FLT_TRUE_MIN; }
    static constexpr float epsilon()       noexcept { return FLT_EPSILON; }
    static constexpr float infinity()      noexcept { return __builtin_huge_valf(); }
    static constexpr float lowest()        noexcept { return -max(); }
    static constexpr float min()           noexcept { return FLT_MIN; }
    static constexpr float max()           noexcept { return FLT_MAX; }
    static constexpr float quiet_NaN()     noexcept { return __builtin_nanf(""); }
    static constexpr float round_error()   noexcept { return 0.5f; }
    static constexpr float signaling_NaN() noexcept { return __builtin_nansf(""); }
};

template <> struct numeric_limits<double> : impl::float_limits_base
{
    static constexpr int digits         = DBL_DIG;
    static constexpr int digits10       = DBL_DIG;
    static constexpr int max_digits10   = DBL_DECIMAL_DIG;
    static constexpr int max_exponent   = DBL_MAX_EXP;
    static constexpr int max_exponent10 = DBL_MAX_10_EXP;
    static constexpr int min_exponent   = DBL_MIN_EXP;
    static constexpr int min_exponent10 = DBL_MIN_10_EXP;

    static constexpr double denorm_min()    noexcept { return DBL_TRUE_MIN; }
    static constexpr double epsilon()       noexcept { return DBL_EPSILON; }
    static constexpr double infinity()      noexcept { return __builtin_huge_val(); }
    static constexpr double lowest()        noexcept { return -max(); }
    static constexpr double min()           noexcept { return DBL_MIN; }
    static constexpr double max()           noexcept { return DBL_MAX; }
    static constexpr double quiet_NaN()     noexcept { return __builtin_nan(""); }
    static constexpr double round_error()   noexcept { return 0.5f; }
    static constexpr double signaling_NaN() noexcept { return __builtin_nans(""); }
};

template <> struct numeric_limits<long double> : impl::float_limits_base
{
    static constexpr int digits         = LDBL_DIG;
    static constexpr int digits10       = LDBL_DIG;
    static constexpr int max_digits10   = LDBL_DECIMAL_DIG;
    static constexpr int max_exponent   = LDBL_MAX_EXP;
    static constexpr int max_exponent10 = LDBL_MAX_10_EXP;
    static constexpr int min_exponent   = LDBL_MIN_EXP;
    static constexpr int min_exponent10 = LDBL_MIN_10_EXP;

    static constexpr long double denorm_min()    noexcept { return LDBL_TRUE_MIN; }
    static constexpr long double epsilon()       noexcept { return LDBL_EPSILON; }
    static constexpr long double infinity()      noexcept { return __builtin_huge_vall(); }
    static constexpr long double lowest()        noexcept { return -max(); }
    static constexpr long double min()           noexcept { return LDBL_MIN; }
    static constexpr long double max()           noexcept { return LDBL_MAX; }
    static constexpr long double quiet_NaN()     noexcept { return __builtin_nanl(""); }
    static constexpr long double round_error()   noexcept { return 0.5f; }
    static constexpr long double signaling_NaN() noexcept { return __builtin_nansl(""); }
};

} // namespace rex