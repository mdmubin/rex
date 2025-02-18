#pragma once

#include "rex/atomic/atomic_impl.hpp"
#include "rex/types.hpp"

/* TYPE ALIASES */

namespace rex
{

using atomic_bool     = atomic<bool>;
using atomic_char     = atomic<char>;
using atomic_schar    = atomic<signed char>;
using atomic_uchar    = atomic<unsigned char>;
using atomic_short    = atomic<short>;
using atomic_ushort   = atomic<unsigned short>;
using atomic_int      = atomic<int>;
using atomic_uint     = atomic<unsigned int>;
using atomic_long     = atomic<long>;
using atomic_ulong    = atomic<unsigned long>;
using atomic_llong    = atomic<long long>;
using atomic_ullong   = atomic<unsigned long long>;
using atomic_char16_t = atomic<char16_t>;
using atomic_char32_t = atomic<char32_t>;
using atomic_wchar_t  = atomic<wchar_t>;
//
using atomic_i8  = atomic<i8>;
using atomic_i16 = atomic<i16>;
using atomic_i32 = atomic<i32>;
using atomic_i64 = atomic<i64>;
using atomic_isz = atomic<isz>;
using atomic_usz = atomic<usz>;
using atomic_u8  = atomic<u8>;
using atomic_u16 = atomic<u16>;
using atomic_u32 = atomic<u32>;
using atomic_u64 = atomic<u64>;

} // namespace rex