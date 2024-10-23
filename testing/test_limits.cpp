#include <limits>
#include <rex/limits.hpp>
#include <rex/types.hpp>

// clang-format off

// denorm_min
static_assert(
    // signed int types
       std::numeric_limits<i8> ::denorm_min() == rex::numeric_limits<i8> ::denorm_min()
    && std::numeric_limits<i16>::denorm_min() == rex::numeric_limits<i16>::denorm_min()
    && std::numeric_limits<i32>::denorm_min() == rex::numeric_limits<i32>::denorm_min()
    && std::numeric_limits<i64>::denorm_min() == rex::numeric_limits<i64>::denorm_min()
    // unsigned int types
    && std::numeric_limits<u8> ::denorm_min() == rex::numeric_limits<u8> ::denorm_min()
    && std::numeric_limits<u16>::denorm_min() == rex::numeric_limits<u16>::denorm_min()
    && std::numeric_limits<u32>::denorm_min() == rex::numeric_limits<u32>::denorm_min()
    && std::numeric_limits<u64>::denorm_min() == rex::numeric_limits<u64>::denorm_min()
    // float types
    && std::numeric_limits<f32>::denorm_min() == rex::numeric_limits<f32>::denorm_min()
    && std::numeric_limits<f64>::denorm_min() == rex::numeric_limits<f64>::denorm_min()
    // size types
    && std::numeric_limits<isz>::denorm_min() == rex::numeric_limits<isz>::denorm_min()
    && std::numeric_limits<usz>::denorm_min() == rex::numeric_limits<usz>::denorm_min()
    // char types
    && std::numeric_limits<wchar_t>::denorm_min() == rex::numeric_limits<wchar_t>::denorm_min()
    && std::numeric_limits<char16_t>::denorm_min() == rex::numeric_limits<char16_t>::denorm_min()
    && std::numeric_limits<char32_t>::denorm_min() == rex::numeric_limits<char32_t>::denorm_min()
);
// epsilon
static_assert(
    // signed int types
       std::numeric_limits<i8> ::epsilon() == rex::numeric_limits<i8> ::epsilon()
    && std::numeric_limits<i16>::epsilon() == rex::numeric_limits<i16>::epsilon()
    && std::numeric_limits<i32>::epsilon() == rex::numeric_limits<i32>::epsilon()
    && std::numeric_limits<i64>::epsilon() == rex::numeric_limits<i64>::epsilon()
    // unsigned int types
    && std::numeric_limits<u8> ::epsilon() == rex::numeric_limits<u8> ::epsilon()
    && std::numeric_limits<u16>::epsilon() == rex::numeric_limits<u16>::epsilon()
    && std::numeric_limits<u32>::epsilon() == rex::numeric_limits<u32>::epsilon()
    && std::numeric_limits<u64>::epsilon() == rex::numeric_limits<u64>::epsilon()
    // float types
    && std::numeric_limits<f32>::epsilon() == rex::numeric_limits<f32>::epsilon()
    && std::numeric_limits<f64>::epsilon() == rex::numeric_limits<f64>::epsilon()
    // size types
    && std::numeric_limits<isz>::epsilon() == rex::numeric_limits<isz>::epsilon()
    && std::numeric_limits<usz>::epsilon() == rex::numeric_limits<usz>::epsilon()
    // char types
    && std::numeric_limits<wchar_t>::epsilon() == rex::numeric_limits<wchar_t>::epsilon()
    && std::numeric_limits<char16_t>::epsilon() == rex::numeric_limits<char16_t>::epsilon()
    && std::numeric_limits<char32_t>::epsilon() == rex::numeric_limits<char32_t>::epsilon()
);
// infinity
static_assert(
    // signed int types
       std::numeric_limits<i8> ::infinity() == rex::numeric_limits<i8> ::infinity()
    && std::numeric_limits<i16>::infinity() == rex::numeric_limits<i16>::infinity()
    && std::numeric_limits<i32>::infinity() == rex::numeric_limits<i32>::infinity()
    && std::numeric_limits<i64>::infinity() == rex::numeric_limits<i64>::infinity()
    // unsigned int types
    && std::numeric_limits<u8> ::infinity() == rex::numeric_limits<u8> ::infinity()
    && std::numeric_limits<u16>::infinity() == rex::numeric_limits<u16>::infinity()
    && std::numeric_limits<u32>::infinity() == rex::numeric_limits<u32>::infinity()
    && std::numeric_limits<u64>::infinity() == rex::numeric_limits<u64>::infinity()
    // float types
    && std::numeric_limits<f32>::infinity() == rex::numeric_limits<f32>::infinity()
    && std::numeric_limits<f64>::infinity() == rex::numeric_limits<f64>::infinity()
    // size types
    && std::numeric_limits<isz>::infinity() == rex::numeric_limits<isz>::infinity()
    && std::numeric_limits<usz>::infinity() == rex::numeric_limits<usz>::infinity()
    // char types
    && std::numeric_limits<wchar_t>::infinity() == rex::numeric_limits<wchar_t>::infinity()
    && std::numeric_limits<char16_t>::infinity() == rex::numeric_limits<char16_t>::infinity()
    && std::numeric_limits<char32_t>::infinity() == rex::numeric_limits<char32_t>::infinity()
);
// lowest
static_assert(
    // signed int types
       std::numeric_limits<i8> ::lowest() == rex::numeric_limits<i8> ::lowest()
    && std::numeric_limits<i16>::lowest() == rex::numeric_limits<i16>::lowest()
    && std::numeric_limits<i32>::lowest() == rex::numeric_limits<i32>::lowest()
    && std::numeric_limits<i64>::lowest() == rex::numeric_limits<i64>::lowest()
    // unsigned int types
    && std::numeric_limits<u8> ::lowest() == rex::numeric_limits<u8> ::lowest()
    && std::numeric_limits<u16>::lowest() == rex::numeric_limits<u16>::lowest()
    && std::numeric_limits<u32>::lowest() == rex::numeric_limits<u32>::lowest()
    && std::numeric_limits<u64>::lowest() == rex::numeric_limits<u64>::lowest()
    // float types
    && std::numeric_limits<f32>::lowest() == rex::numeric_limits<f32>::lowest()
    && std::numeric_limits<f64>::lowest() == rex::numeric_limits<f64>::lowest()
    // size types
    && std::numeric_limits<isz>::lowest() == rex::numeric_limits<isz>::lowest()
    && std::numeric_limits<usz>::lowest() == rex::numeric_limits<usz>::lowest()
    // char types
    && std::numeric_limits<wchar_t>::lowest() == rex::numeric_limits<wchar_t>::lowest()
    && std::numeric_limits<char16_t>::lowest() == rex::numeric_limits<char16_t>::lowest()
    && std::numeric_limits<char32_t>::lowest() == rex::numeric_limits<char32_t>::lowest()
);
// min
static_assert(
    // signed int types
       std::numeric_limits<i8> ::min() == rex::numeric_limits<i8> ::min()
    && std::numeric_limits<i16>::min() == rex::numeric_limits<i16>::min()
    && std::numeric_limits<i32>::min() == rex::numeric_limits<i32>::min()
    && std::numeric_limits<i64>::min() == rex::numeric_limits<i64>::min()
    // unsigned int types
    && std::numeric_limits<u8> ::min() == rex::numeric_limits<u8> ::min()
    && std::numeric_limits<u16>::min() == rex::numeric_limits<u16>::min()
    && std::numeric_limits<u32>::min() == rex::numeric_limits<u32>::min()
    && std::numeric_limits<u64>::min() == rex::numeric_limits<u64>::min()
    // float types
    && std::numeric_limits<f32>::min() == rex::numeric_limits<f32>::min()
    && std::numeric_limits<f64>::min() == rex::numeric_limits<f64>::min()
    // size types
    && std::numeric_limits<isz>::min() == rex::numeric_limits<isz>::min()
    && std::numeric_limits<usz>::min() == rex::numeric_limits<usz>::min()
    // char types
    && std::numeric_limits<wchar_t>::min() == rex::numeric_limits<wchar_t>::min()
    && std::numeric_limits<char16_t>::min() == rex::numeric_limits<char16_t>::min()
    && std::numeric_limits<char32_t>::min() == rex::numeric_limits<char32_t>::min()
);
// max
static_assert(
    // signed int types
       std::numeric_limits<i8> ::max() == rex::numeric_limits<i8> ::max()
    && std::numeric_limits<i16>::max() == rex::numeric_limits<i16>::max()
    && std::numeric_limits<i32>::max() == rex::numeric_limits<i32>::max()
    && std::numeric_limits<i64>::max() == rex::numeric_limits<i64>::max()
    // unsigned int types
    && std::numeric_limits<u8> ::max() == rex::numeric_limits<u8> ::max()
    && std::numeric_limits<u16>::max() == rex::numeric_limits<u16>::max()
    && std::numeric_limits<u32>::max() == rex::numeric_limits<u32>::max()
    && std::numeric_limits<u64>::max() == rex::numeric_limits<u64>::max()
    // float types
    && std::numeric_limits<f32>::max() == rex::numeric_limits<f32>::max()
    && std::numeric_limits<f64>::max() == rex::numeric_limits<f64>::max()
    // size types
    && std::numeric_limits<isz>::max() == rex::numeric_limits<isz>::max()
    && std::numeric_limits<usz>::max() == rex::numeric_limits<usz>::max()
    // char types
    && std::numeric_limits<wchar_t>::max() == rex::numeric_limits<wchar_t>::max()
    && std::numeric_limits<char16_t>::max() == rex::numeric_limits<char16_t>::max()
    && std::numeric_limits<char32_t>::max() == rex::numeric_limits<char32_t>::max()
);
// quiet_NaN
static_assert(
    // signed int types
       std::numeric_limits<i8> ::quiet_NaN() == rex::numeric_limits<i8> ::quiet_NaN()
    && std::numeric_limits<i16>::quiet_NaN() == rex::numeric_limits<i16>::quiet_NaN()
    && std::numeric_limits<i32>::quiet_NaN() == rex::numeric_limits<i32>::quiet_NaN()
    && std::numeric_limits<i64>::quiet_NaN() == rex::numeric_limits<i64>::quiet_NaN()
    // unsigned int types
    && std::numeric_limits<u8> ::quiet_NaN() == rex::numeric_limits<u8> ::quiet_NaN()
    && std::numeric_limits<u16>::quiet_NaN() == rex::numeric_limits<u16>::quiet_NaN()
    && std::numeric_limits<u32>::quiet_NaN() == rex::numeric_limits<u32>::quiet_NaN()
    && std::numeric_limits<u64>::quiet_NaN() == rex::numeric_limits<u64>::quiet_NaN()
    // float types
    // && std::numeric_limits<f32>::quiet_NaN() == rex::numeric_limits<f32>::quiet_NaN() // cannot compare nan values.
    // && std::numeric_limits<f64>::quiet_NaN() == rex::numeric_limits<f64>::quiet_NaN() // cannot compare nan values.
    // size types
    && std::numeric_limits<isz>::quiet_NaN() == rex::numeric_limits<isz>::quiet_NaN()
    && std::numeric_limits<usz>::quiet_NaN() == rex::numeric_limits<usz>::quiet_NaN()
    // char types
    && std::numeric_limits<wchar_t>::quiet_NaN() == rex::numeric_limits<wchar_t>::quiet_NaN()
    && std::numeric_limits<char16_t>::quiet_NaN() == rex::numeric_limits<char16_t>::quiet_NaN()
    && std::numeric_limits<char32_t>::quiet_NaN() == rex::numeric_limits<char32_t>::quiet_NaN()
);
// round_error
static_assert(
    // signed int types
       std::numeric_limits<i8> ::round_error() == rex::numeric_limits<i8> ::round_error()
    && std::numeric_limits<i16>::round_error() == rex::numeric_limits<i16>::round_error()
    && std::numeric_limits<i32>::round_error() == rex::numeric_limits<i32>::round_error()
    && std::numeric_limits<i64>::round_error() == rex::numeric_limits<i64>::round_error()
    // unsigned int types
    && std::numeric_limits<u8> ::round_error() == rex::numeric_limits<u8> ::round_error()
    && std::numeric_limits<u16>::round_error() == rex::numeric_limits<u16>::round_error()
    && std::numeric_limits<u32>::round_error() == rex::numeric_limits<u32>::round_error()
    && std::numeric_limits<u64>::round_error() == rex::numeric_limits<u64>::round_error()
    // float types
    && std::numeric_limits<f32>::round_error() == rex::numeric_limits<f32>::round_error()
    && std::numeric_limits<f64>::round_error() == rex::numeric_limits<f64>::round_error()
    // size types
    && std::numeric_limits<isz>::round_error() == rex::numeric_limits<isz>::round_error()
    && std::numeric_limits<usz>::round_error() == rex::numeric_limits<usz>::round_error()
    // char types
    && std::numeric_limits<wchar_t>::round_error() == rex::numeric_limits<wchar_t>::round_error()
    && std::numeric_limits<char16_t>::round_error() == rex::numeric_limits<char16_t>::round_error()
    && std::numeric_limits<char32_t>::round_error() == rex::numeric_limits<char32_t>::round_error()
);
// signaling_NaN
static_assert(
    // signed int types
       std::numeric_limits<i8> ::signaling_NaN() == rex::numeric_limits<i8> ::signaling_NaN()
    && std::numeric_limits<i16>::signaling_NaN() == rex::numeric_limits<i16>::signaling_NaN()
    && std::numeric_limits<i32>::signaling_NaN() == rex::numeric_limits<i32>::signaling_NaN()
    && std::numeric_limits<i64>::signaling_NaN() == rex::numeric_limits<i64>::signaling_NaN()
    // unsigned int types
    && std::numeric_limits<u8> ::signaling_NaN() == rex::numeric_limits<u8> ::signaling_NaN()
    && std::numeric_limits<u16>::signaling_NaN() == rex::numeric_limits<u16>::signaling_NaN()
    && std::numeric_limits<u32>::signaling_NaN() == rex::numeric_limits<u32>::signaling_NaN()
    && std::numeric_limits<u64>::signaling_NaN() == rex::numeric_limits<u64>::signaling_NaN()
    // float types
    // && std::numeric_limits<f32>::signaling_NaN() == rex::numeric_limits<f32>::signaling_NaN() // cannot compare NaN values.
    // && std::numeric_limits<f64>::signaling_NaN() == rex::numeric_limits<f64>::signaling_NaN() // cannot compare NaN values.
    // size types
    && std::numeric_limits<isz>::signaling_NaN() == rex::numeric_limits<isz>::signaling_NaN()
    && std::numeric_limits<usz>::signaling_NaN() == rex::numeric_limits<usz>::signaling_NaN()
    // char types
    && std::numeric_limits<wchar_t>::signaling_NaN() == rex::numeric_limits<wchar_t>::signaling_NaN()
    && std::numeric_limits<char16_t>::signaling_NaN() == rex::numeric_limits<char16_t>::signaling_NaN()
    && std::numeric_limits<char32_t>::signaling_NaN() == rex::numeric_limits<char32_t>::signaling_NaN()
);

// has_denorm_loss
static_assert(
    // signed int types
       std::numeric_limits<i8> ::has_denorm_loss == rex::numeric_limits<i8> ::has_denorm_loss
    && std::numeric_limits<i16>::has_denorm_loss == rex::numeric_limits<i16>::has_denorm_loss
    && std::numeric_limits<i32>::has_denorm_loss == rex::numeric_limits<i32>::has_denorm_loss
    && std::numeric_limits<i64>::has_denorm_loss == rex::numeric_limits<i64>::has_denorm_loss
    // unsigned int types
    && std::numeric_limits<u8> ::has_denorm_loss == rex::numeric_limits<u8> ::has_denorm_loss
    && std::numeric_limits<u16>::has_denorm_loss == rex::numeric_limits<u16>::has_denorm_loss
    && std::numeric_limits<u32>::has_denorm_loss == rex::numeric_limits<u32>::has_denorm_loss
    && std::numeric_limits<u64>::has_denorm_loss == rex::numeric_limits<u64>::has_denorm_loss
    // float types
    && std::numeric_limits<f32>::has_denorm_loss == rex::numeric_limits<f32>::has_denorm_loss
    && std::numeric_limits<f64>::has_denorm_loss == rex::numeric_limits<f64>::has_denorm_loss
    // size types
    && std::numeric_limits<isz>::has_denorm_loss == rex::numeric_limits<isz>::has_denorm_loss
    && std::numeric_limits<usz>::has_denorm_loss == rex::numeric_limits<usz>::has_denorm_loss
    // char types
    && std::numeric_limits<wchar_t>::has_denorm_loss== rex::numeric_limits<wchar_t>::has_denorm_loss
    && std::numeric_limits<char16_t>::has_denorm_loss == rex::numeric_limits<char16_t>::has_denorm_loss
    && std::numeric_limits<char32_t>::has_denorm_loss == rex::numeric_limits<char32_t>::has_denorm_loss
);
// has_infinity
static_assert(
    // signed int types
       std::numeric_limits<i8> ::has_infinity == rex::numeric_limits<i8> ::has_infinity
    && std::numeric_limits<i16>::has_infinity == rex::numeric_limits<i16>::has_infinity
    && std::numeric_limits<i32>::has_infinity == rex::numeric_limits<i32>::has_infinity
    && std::numeric_limits<i64>::has_infinity == rex::numeric_limits<i64>::has_infinity
    // unsigned int types
    && std::numeric_limits<u8> ::has_infinity == rex::numeric_limits<u8> ::has_infinity
    && std::numeric_limits<u16>::has_infinity == rex::numeric_limits<u16>::has_infinity
    && std::numeric_limits<u32>::has_infinity == rex::numeric_limits<u32>::has_infinity
    && std::numeric_limits<u64>::has_infinity == rex::numeric_limits<u64>::has_infinity
    // float types
    && std::numeric_limits<f32>::has_infinity == rex::numeric_limits<f32>::has_infinity
    && std::numeric_limits<f64>::has_infinity == rex::numeric_limits<f64>::has_infinity
    // size types
    && std::numeric_limits<isz>::has_infinity == rex::numeric_limits<isz>::has_infinity
    && std::numeric_limits<usz>::has_infinity == rex::numeric_limits<usz>::has_infinity
    // char types
    && std::numeric_limits<wchar_t>::has_infinity== rex::numeric_limits<wchar_t>::has_infinity
    && std::numeric_limits<char16_t>::has_infinity == rex::numeric_limits<char16_t>::has_infinity
    && std::numeric_limits<char32_t>::has_infinity == rex::numeric_limits<char32_t>::has_infinity
);
// has_quiet_NaN
static_assert(
    // signed int types
       std::numeric_limits<i8> ::has_quiet_NaN == rex::numeric_limits<i8> ::has_quiet_NaN
    && std::numeric_limits<i16>::has_quiet_NaN == rex::numeric_limits<i16>::has_quiet_NaN
    && std::numeric_limits<i32>::has_quiet_NaN == rex::numeric_limits<i32>::has_quiet_NaN
    && std::numeric_limits<i64>::has_quiet_NaN == rex::numeric_limits<i64>::has_quiet_NaN
    // unsigned int types
    && std::numeric_limits<u8> ::has_quiet_NaN == rex::numeric_limits<u8> ::has_quiet_NaN
    && std::numeric_limits<u16>::has_quiet_NaN == rex::numeric_limits<u16>::has_quiet_NaN
    && std::numeric_limits<u32>::has_quiet_NaN == rex::numeric_limits<u32>::has_quiet_NaN
    && std::numeric_limits<u64>::has_quiet_NaN == rex::numeric_limits<u64>::has_quiet_NaN
    // float types
    && std::numeric_limits<f32>::has_quiet_NaN == rex::numeric_limits<f32>::has_quiet_NaN
    && std::numeric_limits<f64>::has_quiet_NaN == rex::numeric_limits<f64>::has_quiet_NaN
    // size types
    && std::numeric_limits<isz>::has_quiet_NaN == rex::numeric_limits<isz>::has_quiet_NaN
    && std::numeric_limits<usz>::has_quiet_NaN == rex::numeric_limits<usz>::has_quiet_NaN
    // char types
    && std::numeric_limits<wchar_t>::has_quiet_NaN == rex::numeric_limits<wchar_t>::has_quiet_NaN
    && std::numeric_limits<char16_t>::has_quiet_NaN == rex::numeric_limits<char16_t>::has_quiet_NaN
    && std::numeric_limits<char32_t>::has_quiet_NaN == rex::numeric_limits<char32_t>::has_quiet_NaN
);
// has_signaling_NaN
static_assert(
    // signed int types
       std::numeric_limits<i8> ::has_signaling_NaN == rex::numeric_limits<i8> ::has_signaling_NaN
    && std::numeric_limits<i16>::has_signaling_NaN == rex::numeric_limits<i16>::has_signaling_NaN
    && std::numeric_limits<i32>::has_signaling_NaN == rex::numeric_limits<i32>::has_signaling_NaN
    && std::numeric_limits<i64>::has_signaling_NaN == rex::numeric_limits<i64>::has_signaling_NaN
    // unsigned int types
    && std::numeric_limits<u8> ::has_signaling_NaN == rex::numeric_limits<u8> ::has_signaling_NaN
    && std::numeric_limits<u16>::has_signaling_NaN == rex::numeric_limits<u16>::has_signaling_NaN
    && std::numeric_limits<u32>::has_signaling_NaN == rex::numeric_limits<u32>::has_signaling_NaN
    && std::numeric_limits<u64>::has_signaling_NaN == rex::numeric_limits<u64>::has_signaling_NaN
    // float types
    && std::numeric_limits<f32>::has_signaling_NaN == rex::numeric_limits<f32>::has_signaling_NaN
    && std::numeric_limits<f64>::has_signaling_NaN == rex::numeric_limits<f64>::has_signaling_NaN
    // size types
    && std::numeric_limits<isz>::has_signaling_NaN == rex::numeric_limits<isz>::has_signaling_NaN
    && std::numeric_limits<usz>::has_signaling_NaN == rex::numeric_limits<usz>::has_signaling_NaN
    // char types
    && std::numeric_limits<wchar_t>::has_signaling_NaN == rex::numeric_limits<wchar_t>::has_signaling_NaN
    && std::numeric_limits<char16_t>::has_signaling_NaN == rex::numeric_limits<char16_t>::has_signaling_NaN
    && std::numeric_limits<char32_t>::has_signaling_NaN == rex::numeric_limits<char32_t>::has_signaling_NaN
);
// is_bounded
static_assert(
    // signed int types
       std::numeric_limits<i8> ::is_bounded == rex::numeric_limits<i8> ::is_bounded
    && std::numeric_limits<i16>::is_bounded == rex::numeric_limits<i16>::is_bounded
    && std::numeric_limits<i32>::is_bounded == rex::numeric_limits<i32>::is_bounded
    && std::numeric_limits<i64>::is_bounded == rex::numeric_limits<i64>::is_bounded
    // unsigned int types
    && std::numeric_limits<u8> ::is_bounded == rex::numeric_limits<u8> ::is_bounded
    && std::numeric_limits<u16>::is_bounded == rex::numeric_limits<u16>::is_bounded
    && std::numeric_limits<u32>::is_bounded == rex::numeric_limits<u32>::is_bounded
    && std::numeric_limits<u64>::is_bounded == rex::numeric_limits<u64>::is_bounded
    // float types
    && std::numeric_limits<f32>::is_bounded == rex::numeric_limits<f32>::is_bounded
    && std::numeric_limits<f64>::is_bounded == rex::numeric_limits<f64>::is_bounded
    // size types
    && std::numeric_limits<isz>::is_bounded == rex::numeric_limits<isz>::is_bounded
    && std::numeric_limits<usz>::is_bounded == rex::numeric_limits<usz>::is_bounded
    // char types
    && std::numeric_limits<wchar_t>::is_bounded == rex::numeric_limits<wchar_t>::is_bounded
    && std::numeric_limits<char16_t>::is_bounded == rex::numeric_limits<char16_t>::is_bounded
    && std::numeric_limits<char32_t>::is_bounded == rex::numeric_limits<char32_t>::is_bounded
);
// is_exact
static_assert(
    // signed int types
       std::numeric_limits<i8> ::is_exact == rex::numeric_limits<i8> ::is_exact
    && std::numeric_limits<i16>::is_exact == rex::numeric_limits<i16>::is_exact
    && std::numeric_limits<i32>::is_exact == rex::numeric_limits<i32>::is_exact
    && std::numeric_limits<i64>::is_exact == rex::numeric_limits<i64>::is_exact
    // unsigned int types
    && std::numeric_limits<u8> ::is_exact == rex::numeric_limits<u8> ::is_exact
    && std::numeric_limits<u16>::is_exact == rex::numeric_limits<u16>::is_exact
    && std::numeric_limits<u32>::is_exact == rex::numeric_limits<u32>::is_exact
    && std::numeric_limits<u64>::is_exact == rex::numeric_limits<u64>::is_exact
    // float types
    && std::numeric_limits<f32>::is_exact == rex::numeric_limits<f32>::is_exact
    && std::numeric_limits<f64>::is_exact == rex::numeric_limits<f64>::is_exact
    // size types
    && std::numeric_limits<isz>::is_exact == rex::numeric_limits<isz>::is_exact
    && std::numeric_limits<usz>::is_exact == rex::numeric_limits<usz>::is_exact
    // char types
    && std::numeric_limits<wchar_t>::is_exact == rex::numeric_limits<wchar_t>::is_exact
    && std::numeric_limits<char16_t>::is_exact == rex::numeric_limits<char16_t>::is_exact
    && std::numeric_limits<char32_t>::is_exact == rex::numeric_limits<char32_t>::is_exact
);
// is_iec559
static_assert(
    // signed int types
       std::numeric_limits<i8> ::is_iec559 == rex::numeric_limits<i8> ::is_iec559
    && std::numeric_limits<i16>::is_iec559 == rex::numeric_limits<i16>::is_iec559
    && std::numeric_limits<i32>::is_iec559 == rex::numeric_limits<i32>::is_iec559
    && std::numeric_limits<i64>::is_iec559 == rex::numeric_limits<i64>::is_iec559
    // unsigned int types
    && std::numeric_limits<u8> ::is_iec559 == rex::numeric_limits<u8> ::is_iec559
    && std::numeric_limits<u16>::is_iec559 == rex::numeric_limits<u16>::is_iec559
    && std::numeric_limits<u32>::is_iec559 == rex::numeric_limits<u32>::is_iec559
    && std::numeric_limits<u64>::is_iec559 == rex::numeric_limits<u64>::is_iec559
    // float types
    && std::numeric_limits<f32>::is_iec559 == rex::numeric_limits<f32>::is_iec559
    && std::numeric_limits<f64>::is_iec559 == rex::numeric_limits<f64>::is_iec559
    // size types
    && std::numeric_limits<isz>::is_iec559 == rex::numeric_limits<isz>::is_iec559
    && std::numeric_limits<usz>::is_iec559 == rex::numeric_limits<usz>::is_iec559
    // char types
    && std::numeric_limits<wchar_t>::is_iec559 == rex::numeric_limits<wchar_t>::is_iec559
    && std::numeric_limits<char16_t>::is_iec559 == rex::numeric_limits<char16_t>::is_iec559
    && std::numeric_limits<char32_t>::is_iec559 == rex::numeric_limits<char32_t>::is_iec559
);
// is_integer
static_assert(
    // signed int types
       std::numeric_limits<i8> ::is_integer == rex::numeric_limits<i8> ::is_integer
    && std::numeric_limits<i16>::is_integer == rex::numeric_limits<i16>::is_integer
    && std::numeric_limits<i32>::is_integer == rex::numeric_limits<i32>::is_integer
    && std::numeric_limits<i64>::is_integer == rex::numeric_limits<i64>::is_integer
    // unsigned int types
    && std::numeric_limits<u8> ::is_integer == rex::numeric_limits<u8> ::is_integer
    && std::numeric_limits<u16>::is_integer == rex::numeric_limits<u16>::is_integer
    && std::numeric_limits<u32>::is_integer == rex::numeric_limits<u32>::is_integer
    && std::numeric_limits<u64>::is_integer == rex::numeric_limits<u64>::is_integer
    // float types
    && std::numeric_limits<f32>::is_integer == rex::numeric_limits<f32>::is_integer
    && std::numeric_limits<f64>::is_integer == rex::numeric_limits<f64>::is_integer
    // size types
    && std::numeric_limits<isz>::is_integer == rex::numeric_limits<isz>::is_integer
    && std::numeric_limits<usz>::is_integer == rex::numeric_limits<usz>::is_integer
    // char types
    && std::numeric_limits<wchar_t>::is_integer == rex::numeric_limits<wchar_t>::is_integer
    && std::numeric_limits<char16_t>::is_integer == rex::numeric_limits<char16_t>::is_integer
    && std::numeric_limits<char32_t>::is_integer == rex::numeric_limits<char32_t>::is_integer
);
// is_modulo
static_assert(
    // signed int types
       std::numeric_limits<i8> ::is_modulo == rex::numeric_limits<i8> ::is_modulo
    && std::numeric_limits<i16>::is_modulo == rex::numeric_limits<i16>::is_modulo
    && std::numeric_limits<i32>::is_modulo == rex::numeric_limits<i32>::is_modulo
    && std::numeric_limits<i64>::is_modulo == rex::numeric_limits<i64>::is_modulo
    // unsigned int types
    && std::numeric_limits<u8> ::is_modulo == rex::numeric_limits<u8> ::is_modulo
    && std::numeric_limits<u16>::is_modulo == rex::numeric_limits<u16>::is_modulo
    && std::numeric_limits<u32>::is_modulo == rex::numeric_limits<u32>::is_modulo
    && std::numeric_limits<u64>::is_modulo == rex::numeric_limits<u64>::is_modulo
    // float types
    && std::numeric_limits<f32>::is_modulo == rex::numeric_limits<f32>::is_modulo
    && std::numeric_limits<f64>::is_modulo == rex::numeric_limits<f64>::is_modulo
    // size types
    && std::numeric_limits<isz>::is_modulo == rex::numeric_limits<isz>::is_modulo
    && std::numeric_limits<usz>::is_modulo == rex::numeric_limits<usz>::is_modulo
    // char types
    && std::numeric_limits<wchar_t>::is_modulo == rex::numeric_limits<wchar_t>::is_modulo
    && std::numeric_limits<char16_t>::is_modulo == rex::numeric_limits<char16_t>::is_modulo
    && std::numeric_limits<char32_t>::is_modulo == rex::numeric_limits<char32_t>::is_modulo
);
// is_signed
static_assert(
    // signed int types
       std::numeric_limits<i8> ::is_signed == rex::numeric_limits<i8> ::is_signed
    && std::numeric_limits<i16>::is_signed == rex::numeric_limits<i16>::is_signed
    && std::numeric_limits<i32>::is_signed == rex::numeric_limits<i32>::is_signed
    && std::numeric_limits<i64>::is_signed == rex::numeric_limits<i64>::is_signed
    // unsigned int types
    && std::numeric_limits<u8> ::is_signed == rex::numeric_limits<u8> ::is_signed
    && std::numeric_limits<u16>::is_signed == rex::numeric_limits<u16>::is_signed
    && std::numeric_limits<u32>::is_signed == rex::numeric_limits<u32>::is_signed
    && std::numeric_limits<u64>::is_signed == rex::numeric_limits<u64>::is_signed
    // float types
    && std::numeric_limits<f32>::is_signed == rex::numeric_limits<f32>::is_signed
    && std::numeric_limits<f64>::is_signed == rex::numeric_limits<f64>::is_signed
    // size types
    && std::numeric_limits<isz>::is_signed == rex::numeric_limits<isz>::is_signed
    && std::numeric_limits<usz>::is_signed == rex::numeric_limits<usz>::is_signed
    // char types
    && std::numeric_limits<wchar_t>::is_signed == rex::numeric_limits<wchar_t>::is_signed
    && std::numeric_limits<char16_t>::is_signed == rex::numeric_limits<char16_t>::is_signed
    && std::numeric_limits<char32_t>::is_signed == rex::numeric_limits<char32_t>::is_signed
);
// is_specialized
static_assert(
    // signed int types
       std::numeric_limits<i8> ::is_specialized == rex::numeric_limits<i8> ::is_specialized
    && std::numeric_limits<i16>::is_specialized == rex::numeric_limits<i16>::is_specialized
    && std::numeric_limits<i32>::is_specialized == rex::numeric_limits<i32>::is_specialized
    && std::numeric_limits<i64>::is_specialized == rex::numeric_limits<i64>::is_specialized
    // unsigned int types
    && std::numeric_limits<u8> ::is_specialized == rex::numeric_limits<u8> ::is_specialized
    && std::numeric_limits<u16>::is_specialized == rex::numeric_limits<u16>::is_specialized
    && std::numeric_limits<u32>::is_specialized == rex::numeric_limits<u32>::is_specialized
    && std::numeric_limits<u64>::is_specialized == rex::numeric_limits<u64>::is_specialized
    // float types
    && std::numeric_limits<f32>::is_specialized == rex::numeric_limits<f32>::is_specialized
    && std::numeric_limits<f64>::is_specialized == rex::numeric_limits<f64>::is_specialized
    // size types
    && std::numeric_limits<isz>::is_specialized == rex::numeric_limits<isz>::is_specialized
    && std::numeric_limits<usz>::is_specialized == rex::numeric_limits<usz>::is_specialized
    // char types
    && std::numeric_limits<wchar_t>::is_specialized == rex::numeric_limits<wchar_t>::is_specialized
    && std::numeric_limits<char16_t>::is_specialized == rex::numeric_limits<char16_t>::is_specialized
    && std::numeric_limits<char32_t>::is_specialized == rex::numeric_limits<char32_t>::is_specialized
);
// tinyness_before
static_assert(
    // signed int types
       std::numeric_limits<i8> ::tinyness_before == rex::numeric_limits<i8> ::tinyness_before
    && std::numeric_limits<i16>::tinyness_before == rex::numeric_limits<i16>::tinyness_before
    && std::numeric_limits<i32>::tinyness_before == rex::numeric_limits<i32>::tinyness_before
    && std::numeric_limits<i64>::tinyness_before == rex::numeric_limits<i64>::tinyness_before
    // unsigned int types
    && std::numeric_limits<u8> ::tinyness_before == rex::numeric_limits<u8> ::tinyness_before
    && std::numeric_limits<u16>::tinyness_before == rex::numeric_limits<u16>::tinyness_before
    && std::numeric_limits<u32>::tinyness_before == rex::numeric_limits<u32>::tinyness_before
    && std::numeric_limits<u64>::tinyness_before == rex::numeric_limits<u64>::tinyness_before
    // float types
    && std::numeric_limits<f32>::tinyness_before == rex::numeric_limits<f32>::tinyness_before
    && std::numeric_limits<f64>::tinyness_before == rex::numeric_limits<f64>::tinyness_before
    // size types
    && std::numeric_limits<isz>::tinyness_before == rex::numeric_limits<isz>::tinyness_before
    && std::numeric_limits<usz>::tinyness_before == rex::numeric_limits<usz>::tinyness_before
    // char types
    && std::numeric_limits<wchar_t>::tinyness_before == rex::numeric_limits<wchar_t>::tinyness_before
    && std::numeric_limits<char16_t>::tinyness_before == rex::numeric_limits<char16_t>::tinyness_before
    && std::numeric_limits<char32_t>::tinyness_before == rex::numeric_limits<char32_t>::tinyness_before
);
// traps
static_assert(
    // signed int types
       std::numeric_limits<i8> ::traps == rex::numeric_limits<i8> ::traps
    && std::numeric_limits<i16>::traps == rex::numeric_limits<i16>::traps
    && std::numeric_limits<i32>::traps == rex::numeric_limits<i32>::traps
    && std::numeric_limits<i64>::traps == rex::numeric_limits<i64>::traps
    // // unsigned int types
    && std::numeric_limits<u8> ::traps == rex::numeric_limits<u8> ::traps
    && std::numeric_limits<u16>::traps == rex::numeric_limits<u16>::traps
    && std::numeric_limits<u32>::traps == rex::numeric_limits<u32>::traps
    && std::numeric_limits<u64>::traps == rex::numeric_limits<u64>::traps
    // float types
    && std::numeric_limits<f32>::traps == rex::numeric_limits<f32>::traps
    && std::numeric_limits<f64>::traps == rex::numeric_limits<f64>::traps
    // size types
    && std::numeric_limits<isz>::traps == rex::numeric_limits<isz>::traps
    && std::numeric_limits<usz>::traps == rex::numeric_limits<usz>::traps
    // char types
    && std::numeric_limits<wchar_t>::traps == rex::numeric_limits<wchar_t>::traps
    && std::numeric_limits<char16_t>::traps == rex::numeric_limits<char16_t>::traps
    && std::numeric_limits<char32_t>::traps == rex::numeric_limits<char32_t>::traps
);
// digits
static_assert(
    // signed int types
       std::numeric_limits<i8> ::digits == rex::numeric_limits<i8> ::digits
    && std::numeric_limits<i16>::digits == rex::numeric_limits<i16>::digits
    && std::numeric_limits<i32>::digits == rex::numeric_limits<i32>::digits
    && std::numeric_limits<i64>::digits == rex::numeric_limits<i64>::digits
    // unsigned int types
    && std::numeric_limits<u8> ::digits == rex::numeric_limits<u8> ::digits
    && std::numeric_limits<u16>::digits == rex::numeric_limits<u16>::digits
    && std::numeric_limits<u32>::digits == rex::numeric_limits<u32>::digits
    && std::numeric_limits<u64>::digits == rex::numeric_limits<u64>::digits
    // float types
    && std::numeric_limits<f32>::digits == rex::numeric_limits<f32>::digits
    && std::numeric_limits<f64>::digits == rex::numeric_limits<f64>::digits
    // size types
    && std::numeric_limits<isz>::digits == rex::numeric_limits<isz>::digits
    && std::numeric_limits<usz>::digits == rex::numeric_limits<usz>::digits
    // char types
    && std::numeric_limits<wchar_t>::digits == rex::numeric_limits<wchar_t>::digits
    && std::numeric_limits<char16_t>::digits == rex::numeric_limits<char16_t>::digits
    && std::numeric_limits<char32_t>::digits == rex::numeric_limits<char32_t>::digits
);
// digits10
static_assert(
    // signed int types
       std::numeric_limits<i8> ::digits10 == rex::numeric_limits<i8> ::digits10
    && std::numeric_limits<i16>::digits10 == rex::numeric_limits<i16>::digits10
    && std::numeric_limits<i32>::digits10 == rex::numeric_limits<i32>::digits10
    && std::numeric_limits<i64>::digits10 == rex::numeric_limits<i64>::digits10
    // unsigned int types
    && std::numeric_limits<u8> ::digits10 == rex::numeric_limits<u8> ::digits10
    && std::numeric_limits<u16>::digits10 == rex::numeric_limits<u16>::digits10
    && std::numeric_limits<u32>::digits10 == rex::numeric_limits<u32>::digits10
    && std::numeric_limits<u64>::digits10 == rex::numeric_limits<u64>::digits10
    // float types
    && std::numeric_limits<f32>::digits10 == rex::numeric_limits<f32>::digits10
    && std::numeric_limits<f64>::digits10 == rex::numeric_limits<f64>::digits10
    // size types
    && std::numeric_limits<isz>::digits10 == rex::numeric_limits<isz>::digits10
    && std::numeric_limits<usz>::digits10 == rex::numeric_limits<usz>::digits10
    // char types
    && std::numeric_limits<wchar_t>::digits10 == rex::numeric_limits<wchar_t>::digits10
    && std::numeric_limits<char16_t>::digits10 == rex::numeric_limits<char16_t>::digits10
    && std::numeric_limits<char32_t>::digits10 == rex::numeric_limits<char32_t>::digits10
);
// max_digits10
static_assert(
    // signed int types
       std::numeric_limits<i8> ::max_digits10 == rex::numeric_limits<i8> ::max_digits10
    && std::numeric_limits<i16>::max_digits10 == rex::numeric_limits<i16>::max_digits10
    && std::numeric_limits<i32>::max_digits10 == rex::numeric_limits<i32>::max_digits10
    && std::numeric_limits<i64>::max_digits10 == rex::numeric_limits<i64>::max_digits10
    // unsigned int types
    && std::numeric_limits<u8> ::max_digits10 == rex::numeric_limits<u8> ::max_digits10
    && std::numeric_limits<u16>::max_digits10 == rex::numeric_limits<u16>::max_digits10
    && std::numeric_limits<u32>::max_digits10 == rex::numeric_limits<u32>::max_digits10
    && std::numeric_limits<u64>::max_digits10 == rex::numeric_limits<u64>::max_digits10
    // float types
    && std::numeric_limits<f32>::max_digits10 == rex::numeric_limits<f32>::max_digits10
    && std::numeric_limits<f64>::max_digits10 == rex::numeric_limits<f64>::max_digits10
    // size types
    && std::numeric_limits<isz>::max_digits10 == rex::numeric_limits<isz>::max_digits10
    && std::numeric_limits<usz>::max_digits10 == rex::numeric_limits<usz>::max_digits10
    // char types
    && std::numeric_limits<wchar_t>::max_digits10 == rex::numeric_limits<wchar_t>::max_digits10
    && std::numeric_limits<char16_t>::max_digits10 == rex::numeric_limits<char16_t>::max_digits10
    && std::numeric_limits<char32_t>::max_digits10 == rex::numeric_limits<char32_t>::max_digits10
);
// max_exponent
static_assert(
    // signed int types
       std::numeric_limits<i8> ::max_exponent == rex::numeric_limits<i8> ::max_exponent
    && std::numeric_limits<i16>::max_exponent == rex::numeric_limits<i16>::max_exponent
    && std::numeric_limits<i32>::max_exponent == rex::numeric_limits<i32>::max_exponent
    && std::numeric_limits<i64>::max_exponent == rex::numeric_limits<i64>::max_exponent
    // unsigned int types
    && std::numeric_limits<u8> ::max_exponent == rex::numeric_limits<u8> ::max_exponent
    && std::numeric_limits<u16>::max_exponent == rex::numeric_limits<u16>::max_exponent
    && std::numeric_limits<u32>::max_exponent == rex::numeric_limits<u32>::max_exponent
    && std::numeric_limits<u64>::max_exponent == rex::numeric_limits<u64>::max_exponent
    // float types
    && std::numeric_limits<f32>::max_exponent == rex::numeric_limits<f32>::max_exponent
    && std::numeric_limits<f64>::max_exponent == rex::numeric_limits<f64>::max_exponent
    // size types
    && std::numeric_limits<isz>::max_exponent == rex::numeric_limits<isz>::max_exponent
    && std::numeric_limits<usz>::max_exponent == rex::numeric_limits<usz>::max_exponent
    // char types
    && std::numeric_limits<wchar_t>::max_exponent == rex::numeric_limits<wchar_t>::max_exponent
    && std::numeric_limits<char16_t>::max_exponent == rex::numeric_limits<char16_t>::max_exponent
    && std::numeric_limits<char32_t>::max_exponent == rex::numeric_limits<char32_t>::max_exponent
);
// max_exponent10
static_assert(
    // signed int types
       std::numeric_limits<i8> ::max_exponent10 == rex::numeric_limits<i8> ::max_exponent10
    && std::numeric_limits<i16>::max_exponent10 == rex::numeric_limits<i16>::max_exponent10
    && std::numeric_limits<i32>::max_exponent10 == rex::numeric_limits<i32>::max_exponent10
    && std::numeric_limits<i64>::max_exponent10 == rex::numeric_limits<i64>::max_exponent10
    // unsigned int types
    && std::numeric_limits<u8> ::max_exponent10 == rex::numeric_limits<u8> ::max_exponent10
    && std::numeric_limits<u16>::max_exponent10 == rex::numeric_limits<u16>::max_exponent10
    && std::numeric_limits<u32>::max_exponent10 == rex::numeric_limits<u32>::max_exponent10
    && std::numeric_limits<u64>::max_exponent10 == rex::numeric_limits<u64>::max_exponent10
    // float types
    && std::numeric_limits<f32>::max_exponent10 == rex::numeric_limits<f32>::max_exponent10
    && std::numeric_limits<f64>::max_exponent10 == rex::numeric_limits<f64>::max_exponent10
    // size types
    && std::numeric_limits<isz>::max_exponent10 == rex::numeric_limits<isz>::max_exponent10
    && std::numeric_limits<usz>::max_exponent10 == rex::numeric_limits<usz>::max_exponent10
    // char types
    && std::numeric_limits<wchar_t>::max_exponent10 == rex::numeric_limits<wchar_t>::max_exponent10
    && std::numeric_limits<char16_t>::max_exponent10 == rex::numeric_limits<char16_t>::max_exponent10
    && std::numeric_limits<char32_t>::max_exponent10 == rex::numeric_limits<char32_t>::max_exponent10
);
// min_exponent
static_assert(
    // signed int types
       std::numeric_limits<i8> ::min_exponent == rex::numeric_limits<i8> ::min_exponent
    && std::numeric_limits<i16>::min_exponent == rex::numeric_limits<i16>::min_exponent
    && std::numeric_limits<i32>::min_exponent == rex::numeric_limits<i32>::min_exponent
    && std::numeric_limits<i64>::min_exponent == rex::numeric_limits<i64>::min_exponent
    // unsigned int types
    && std::numeric_limits<u8> ::min_exponent == rex::numeric_limits<u8> ::min_exponent
    && std::numeric_limits<u16>::min_exponent == rex::numeric_limits<u16>::min_exponent
    && std::numeric_limits<u32>::min_exponent == rex::numeric_limits<u32>::min_exponent
    && std::numeric_limits<u64>::min_exponent == rex::numeric_limits<u64>::min_exponent
    // float types
    && std::numeric_limits<f32>::min_exponent == rex::numeric_limits<f32>::min_exponent
    && std::numeric_limits<f64>::min_exponent == rex::numeric_limits<f64>::min_exponent
    // size types
    && std::numeric_limits<isz>::min_exponent == rex::numeric_limits<isz>::min_exponent
    && std::numeric_limits<usz>::min_exponent == rex::numeric_limits<usz>::min_exponent
    // char types
    && std::numeric_limits<wchar_t>::min_exponent == rex::numeric_limits<wchar_t>::min_exponent
    && std::numeric_limits<char16_t>::min_exponent == rex::numeric_limits<char16_t>::min_exponent
    && std::numeric_limits<char32_t>::min_exponent == rex::numeric_limits<char32_t>::min_exponent
);
// min_exponent10
static_assert(
    // signed int types
       std::numeric_limits<i8> ::min_exponent10 == rex::numeric_limits<i8> ::min_exponent10
    && std::numeric_limits<i16>::min_exponent10 == rex::numeric_limits<i16>::min_exponent10
    && std::numeric_limits<i32>::min_exponent10 == rex::numeric_limits<i32>::min_exponent10
    && std::numeric_limits<i64>::min_exponent10 == rex::numeric_limits<i64>::min_exponent10
    // unsigned int types
    && std::numeric_limits<u8> ::min_exponent10 == rex::numeric_limits<u8> ::min_exponent10
    && std::numeric_limits<u16>::min_exponent10 == rex::numeric_limits<u16>::min_exponent10
    && std::numeric_limits<u32>::min_exponent10 == rex::numeric_limits<u32>::min_exponent10
    && std::numeric_limits<u64>::min_exponent10 == rex::numeric_limits<u64>::min_exponent10
    // float types
    && std::numeric_limits<f32>::min_exponent10 == rex::numeric_limits<f32>::min_exponent10
    && std::numeric_limits<f64>::min_exponent10 == rex::numeric_limits<f64>::min_exponent10
    // size types
    && std::numeric_limits<isz>::min_exponent10 == rex::numeric_limits<isz>::min_exponent10
    && std::numeric_limits<usz>::min_exponent10 == rex::numeric_limits<usz>::min_exponent10
    // char types
    && std::numeric_limits<wchar_t>::min_exponent10 == rex::numeric_limits<wchar_t>::min_exponent10
    && std::numeric_limits<char16_t>::min_exponent10 == rex::numeric_limits<char16_t>::min_exponent10
    && std::numeric_limits<char32_t>::min_exponent10 == rex::numeric_limits<char32_t>::min_exponent10
);
// radix
static_assert(
    // signed int types
       std::numeric_limits<i8> ::radix == rex::numeric_limits<i8> ::radix
    && std::numeric_limits<i16>::radix == rex::numeric_limits<i16>::radix
    && std::numeric_limits<i32>::radix == rex::numeric_limits<i32>::radix
    && std::numeric_limits<i64>::radix == rex::numeric_limits<i64>::radix
    // unsigned int types
    && std::numeric_limits<u8> ::radix == rex::numeric_limits<u8> ::radix
    && std::numeric_limits<u16>::radix == rex::numeric_limits<u16>::radix
    && std::numeric_limits<u32>::radix == rex::numeric_limits<u32>::radix
    && std::numeric_limits<u64>::radix == rex::numeric_limits<u64>::radix
    // float types
    && std::numeric_limits<f32>::radix == rex::numeric_limits<f32>::radix
    && std::numeric_limits<f64>::radix == rex::numeric_limits<f64>::radix
    // size types
    && std::numeric_limits<isz>::radix == rex::numeric_limits<isz>::radix
    && std::numeric_limits<usz>::radix == rex::numeric_limits<usz>::radix
    // char types
    && std::numeric_limits<wchar_t>::radix == rex::numeric_limits<wchar_t>::radix
    && std::numeric_limits<char16_t>::radix == rex::numeric_limits<char16_t>::radix
    && std::numeric_limits<char32_t>::radix == rex::numeric_limits<char32_t>::radix
);
// round_style;
static_assert(
    // signed int types
       static_cast<int>(std::numeric_limits<i8> ::round_style) == static_cast<int>(rex::numeric_limits<i8> ::round_style)
    && static_cast<int>(std::numeric_limits<i16>::round_style) == static_cast<int>(rex::numeric_limits<i16>::round_style)
    && static_cast<int>(std::numeric_limits<i32>::round_style) == static_cast<int>(rex::numeric_limits<i32>::round_style)
    && static_cast<int>(std::numeric_limits<i64>::round_style) == static_cast<int>(rex::numeric_limits<i64>::round_style)
    // unsigned int types
    && static_cast<int>(std::numeric_limits<u8> ::round_style) == static_cast<int>(rex::numeric_limits<u8> ::round_style)
    && static_cast<int>(std::numeric_limits<u16>::round_style) == static_cast<int>(rex::numeric_limits<u16>::round_style)
    && static_cast<int>(std::numeric_limits<u32>::round_style) == static_cast<int>(rex::numeric_limits<u32>::round_style)
    && static_cast<int>(std::numeric_limits<u64>::round_style) == static_cast<int>(rex::numeric_limits<u64>::round_style)
    // float types
    && static_cast<int>(std::numeric_limits<f32>::round_style) == static_cast<int>(rex::numeric_limits<f32>::round_style)
    && static_cast<int>(std::numeric_limits<f64>::round_style) == static_cast<int>(rex::numeric_limits<f64>::round_style)
    // size types
    && static_cast<int>(std::numeric_limits<isz>::round_style) == static_cast<int>(rex::numeric_limits<isz>::round_style)
    && static_cast<int>(std::numeric_limits<usz>::round_style) == static_cast<int>(rex::numeric_limits<usz>::round_style)
    // char types
    && static_cast<int>(std::numeric_limits<wchar_t>::round_style) == static_cast<int>(rex::numeric_limits<wchar_t>::round_style)
    && static_cast<int>(std::numeric_limits<char16_t>::round_style) == static_cast<int>(rex::numeric_limits<char16_t>::round_style)
    && static_cast<int>(std::numeric_limits<char32_t>::round_style) == static_cast<int>(rex::numeric_limits<char32_t>::round_style)
);
// has_denorm;
static_assert(
    // signed int types
       static_cast<int>(std::numeric_limits<i8> ::has_denorm) == static_cast<int>(rex::numeric_limits<i8> ::has_denorm)
    && static_cast<int>(std::numeric_limits<i16>::has_denorm) == static_cast<int>(rex::numeric_limits<i16>::has_denorm)
    && static_cast<int>(std::numeric_limits<i32>::has_denorm) == static_cast<int>(rex::numeric_limits<i32>::has_denorm)
    && static_cast<int>(std::numeric_limits<i64>::has_denorm) == static_cast<int>(rex::numeric_limits<i64>::has_denorm)
    // unsigned int types
    && static_cast<int>(std::numeric_limits<u8> ::has_denorm) == static_cast<int>(rex::numeric_limits<u8> ::has_denorm)
    && static_cast<int>(std::numeric_limits<u16>::has_denorm) == static_cast<int>(rex::numeric_limits<u16>::has_denorm)
    && static_cast<int>(std::numeric_limits<u32>::has_denorm) == static_cast<int>(rex::numeric_limits<u32>::has_denorm)
    && static_cast<int>(std::numeric_limits<u64>::has_denorm) == static_cast<int>(rex::numeric_limits<u64>::has_denorm)
    // float types
    && static_cast<int>(std::numeric_limits<f32>::has_denorm) == static_cast<int>(rex::numeric_limits<f32>::has_denorm)
    && static_cast<int>(std::numeric_limits<f64>::has_denorm) == static_cast<int>(rex::numeric_limits<f64>::has_denorm)
    // size types
    && static_cast<int>(std::numeric_limits<isz>::has_denorm) == static_cast<int>(rex::numeric_limits<isz>::has_denorm)
    && static_cast<int>(std::numeric_limits<usz>::has_denorm) == static_cast<int>(rex::numeric_limits<usz>::has_denorm)
    // char types
    && static_cast<int>(std::numeric_limits<wchar_t>::has_denorm) == static_cast<int>(rex::numeric_limits<wchar_t>::has_denorm)
    && static_cast<int>(std::numeric_limits<char16_t>::has_denorm) == static_cast<int>(rex::numeric_limits<char16_t>::has_denorm)
    && static_cast<int>(std::numeric_limits<char32_t>::has_denorm) == static_cast<int>(rex::numeric_limits<char32_t>::has_denorm)
);