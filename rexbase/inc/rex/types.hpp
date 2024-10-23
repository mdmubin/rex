#pragma once

#include <cfloat>
#include <cstdint>
#include <cstddef>

/* Signed Integer Types */

/// @brief  8-bit signed integer.
using i8 = int8_t;
/// @brief 16-bit signed integer.
using i16 = int16_t;
/// @brief 32-bit signed integer.
using i32 = int32_t;
/// @brief 64-bit signed integer.
using i64 = int64_t;

/* Unsigned Integer Types */

/// @brief  8-bit unsigned integer.
using u8 = uint8_t;
/// @brief 16-bit unsigned integer.
using u16 = uint16_t;
/// @brief 32-bit unsigned integer
using u32 = uint32_t;
/// @brief 64-bit unsigned integer.
using u64 = uint64_t;

/* Floating Point Types */

/// @brief 32-bit floating point number.
using f32 = float;
/// @brief 64-bit floating point number.
using f64 = double;

/* Size Types */

/// @brief Signed integer type for representing difference between pointers or sizes.
using isz = decltype(static_cast<int *>(nullptr) - static_cast<int *>(nullptr));
/// @brief Unsigned integer type for representing sizes.
using usz = decltype(sizeof(0));

/* String Types */

/// @brief Multibyte string type.
using cstr = const char *;
/// @brief Wide character string type.
using wstr = const wchar_t *;

//

namespace rex
{
using ::cstr, ::wstr;            // string types
using ::f32, ::f64;              // float types
using ::i8, ::i16, ::i32, ::i64; // signed integer types
using ::isz, ::usz;              // size types
using ::u8, ::u16, ::u32, ::u64; // unsigned size types
} // namespace rex