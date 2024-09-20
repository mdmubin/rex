#include <gtest/gtest.h>
#include <rex/types.hpp>

static_assert(sizeof(i8) == 1, "Size of i8 is expected to be 1 bytes.");
static_assert(sizeof(i16) == 2, "Size of i16 is expected to be 2 bytes.");
static_assert(sizeof(i32) == 4, "Size of i32 is expected to be 4 bytes.");
static_assert(sizeof(i64) == 8, "Size of i64 is expected to be 8 bytes.");

static_assert(sizeof(u8) == 1, "Size of u8 is expected to be 1 bytes.");
static_assert(sizeof(u16) == 2, "Size of u16 is expected to be 2 bytes.");
static_assert(sizeof(u32) == 4, "Size of u32 is expected to be 4 bytes.");
static_assert(sizeof(u64) == 8, "Size of u64 is expected to be 8 bytes.");

static_assert(sizeof(f32) == 4, "Size of f32 is expected to be 4 bytes.");
static_assert(sizeof(f64) == 8, "Size of f64 is expected to be 4 bytes.");