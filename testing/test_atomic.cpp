#include <gtest/gtest.h>
#include <rex/atomic.hpp>

struct Sample128Bit_1
{
    i32 a, b, c, d;

    bool operator==(const Sample128Bit_1 &other) const
    {
        return a == other.a && b == other.b && c == other.c && d == other.d;
    }
};

struct Sample128Bit_2
{
    i64 a, b;

    bool operator==(const Sample128Bit_2 &other) const
    {
        return a == other.a && b == other.b;
    }
};

TEST(AtomicTest, ConstructionTest)
{
    {
        rex::atomic_i8 atomicI8{};
        rex::atomic_i16 atomicI16{};
        rex::atomic_i32 atomicI32{};
        rex::atomic_i64 atomicI64{};
        rex::atomic_u8 atomicU8{};
        rex::atomic_u16 atomicU16{};
        rex::atomic_u32 atomicU32{};
        rex::atomic_u64 atomicU64{};
        rex::atomic_wchar_t atomicWcharT{};
        rex::atomic_char16_t atomicChar16T{};
        rex::atomic_char32_t atomicChar32T{};
        rex::atomic<Sample128Bit_1> atomicSample1{};
        rex::atomic<Sample128Bit_2> atomicSample2{};
    }
    {
        constexpr rex::atomic_i8 atomicI8{1};
        constexpr rex::atomic_i16 atomicI16{1};
        constexpr rex::atomic_i32 atomicI32{1};
        constexpr rex::atomic_i64 atomicI64{1};
        constexpr rex::atomic_u8 atomicU8{1};
        constexpr rex::atomic_u16 atomicU16{1};
        constexpr rex::atomic_u32 atomicU32{1};
        constexpr rex::atomic_u64 atomicU64{1};
        constexpr rex::atomic_wchar_t atomicWcharT{1};
        constexpr rex::atomic_char16_t atomicChar16T{1};
        constexpr rex::atomic_char32_t atomicChar32T{1};
        constexpr rex::atomic<Sample128Bit_1> atomicSample1{
            {1, 2, 3, 4}
        };
        constexpr rex::atomic<Sample128Bit_2> atomicSample2{
            {1, 2}
        };
    }
}

TEST(AtomicTest, LoadTest)
{
    using namespace rex;
    {
        constexpr atomic_i8 i{1};
        EXPECT_EQ(i.load(memory_order_relaxed), 1);
        EXPECT_EQ(i.load(memory_order_consume), 1);
        EXPECT_EQ(i.load(memory_order_acquire), 1);
        EXPECT_EQ(i.load(memory_order_seq_cst), 1);

        constexpr atomic_i8 j{5};
        EXPECT_NE(j.load(memory_order_relaxed), i8{});
        EXPECT_NE(j.load(memory_order_consume), i8{});
        EXPECT_NE(j.load(memory_order_acquire), i8{});
        EXPECT_NE(j.load(memory_order_seq_cst), i8{});

        EXPECT_DEATH(i.load(memory_order_release), "Invalid memory order constraint for atomic load.");
        EXPECT_DEATH(i.load(memory_order_acq_rel), "Invalid memory order constraint for atomic load.");
    }
    {
        atomic x{
            Sample128Bit_1{1, 2, 3, 4}
        };
        EXPECT_EQ(x.load(), (Sample128Bit_1{1, 2, 3, 4}));

        atomic y{
            Sample128Bit_2{5, 6}
        };
        EXPECT_EQ(y.load(), (Sample128Bit_2{5, 6}));
    }
}

TEST(AtomicTest, StoreTest)
{
    using namespace rex;
    {
        atomic_i16 i{};
        i.store(1, memory_order_relaxed);
        EXPECT_EQ(i.load(), 1);
        i.store(4, memory_order_release);
        EXPECT_EQ(i.load(), 4);
        i.store(6, memory_order_seq_cst);
        EXPECT_EQ(i.load(), 6);

        EXPECT_DEATH(i.store(2, memory_order_consume), "Invalid memory order constraint for atomic store.");
        EXPECT_DEATH(i.store(3, memory_order_acquire), "Invalid memory order constraint for atomic store.");
        EXPECT_DEATH(i.store(5, memory_order_acq_rel), "Invalid memory order constraint for atomic store.");

        atomic<Sample128Bit_1> x{};
        x.store({5, 6, 7, 8});
        EXPECT_EQ(x.load(), (Sample128Bit_1{5, 6, 7, 8}));

        atomic<Sample128Bit_2> y{};
        y.store({4, 6});
        EXPECT_EQ(y.load(), (Sample128Bit_2{4, 6}));
    }
}

TEST(AtomicTest, ExchangeTest)
{
    using namespace rex;
    {
        atomic<i32> i{INT32_MIN};
        EXPECT_EQ(i.exchange(50), INT32_MIN);
        EXPECT_EQ(i.load(), 50);
        EXPECT_EQ(i.exchange(2), 50);
        EXPECT_EQ(i.load(), 2);
        EXPECT_EQ(i.exchange(INT32_MAX), 2);
        EXPECT_EQ(i.load(), INT32_MAX);

        atomic<Sample128Bit_1> x{};
        x.store({5, 6, 7, 8});
        EXPECT_EQ(x.exchange({1, 2, 3, 4}), (Sample128Bit_1{5, 6, 7, 8}));
        EXPECT_EQ(x.load(), (Sample128Bit_1{1, 2, 3, 4}));

        atomic<Sample128Bit_2> y{};
        y.store({4, 6});
        EXPECT_EQ(y.exchange({99, 99}), (Sample128Bit_2{4, 6}));
        EXPECT_EQ(y.load(), (Sample128Bit_2{99, 99}));
    }
}