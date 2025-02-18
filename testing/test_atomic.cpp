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

struct Sample24Bit
{
    i8 a, b, c;

    bool operator==(const Sample24Bit &other) const
    {
        return a == other.a && b == other.b && c == other.c;
    }
};

struct Sample96Bits
{
    i32 a, b, c;

    bool operator==(const Sample24Bit &other) const
    {
        return a == other.a && b == other.b && c == other.c;
    }
};

TEST(AtomicTest, ConstructionTest)
{
    using namespace rex;
    {
        atomic_i8 atomicI8{};
        atomic_i16 atomicI16{};
        atomic_i32 atomicI32{};
        atomic_i64 atomicI64{};
        atomic_u8 atomicU8{};
        atomic_u16 atomicU16{};
        atomic_u32 atomicU32{};
        atomic_u64 atomicU64{};
        atomic_wchar_t atomicWcharT{};
        atomic_char16_t atomicChar16T{};
        atomic_char32_t atomicChar32T{};
        atomic<Sample128Bit_1> atomicSample1{};
        atomic<Sample128Bit_2> atomicSample2{};
    }
    {
        constexpr atomic_i8 atomicI8{1};
        constexpr atomic_i16 atomicI16{1};
        constexpr atomic_i32 atomicI32{1};
        constexpr atomic_i64 atomicI64{1};
        constexpr atomic_u8 atomicU8{1};
        constexpr atomic_u16 atomicU16{1};
        constexpr atomic_u32 atomicU32{1};
        constexpr atomic_u64 atomicU64{1};
        constexpr atomic_wchar_t atomicWcharT{1};
        constexpr atomic_char16_t atomicChar16T{1};
        constexpr atomic_char32_t atomicChar32T{1};
        constexpr atomic<Sample128Bit_1> atomicSample1{
            {1, 2, 3, 4}
        };
        constexpr atomic<Sample128Bit_2> atomicSample2{
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

        // these generate warnings on GCC
        // EXPECT_DEATH(i.load(memory_order_release), "Invalid memory order constraint for atomic load.");
        // EXPECT_DEATH(i.load(memory_order_acq_rel), "Invalid memory order constraint for atomic load.");
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

        // these generate warnings on GCC
        // EXPECT_DEATH(i.store(2, memory_order_consume), "Invalid memory order constraint for atomic store.");
        // EXPECT_DEATH(i.store(3, memory_order_acquire), "Invalid memory order constraint for atomic store.");
        // EXPECT_DEATH(i.store(5, memory_order_acq_rel), "Invalid memory order constraint for atomic store.");

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
        atomic_i32 i{INT32_MIN};
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

TEST(AtomicTest, CompareExchange)
{
    using namespace rex;
    // NOTE: On x86 systems, both compare_exchange_weak and compare_exchange_strong are implemented using a cmpxchg
    // instruction. i.e. both use a compare-and-swap operation, which is unlike other processors (RISC-V or ARM) which
    // use a Load-Linked/Store-Conditional instruction. In other words, in x86, both compare_exchange_weak and
    // compare_exchange_strong are the same.
    {
        {
            atomic_i64 i{INT64_MIN};
            i64 j = 0;
            EXPECT_FALSE(i.compare_exchange_weak(j, 1));
            EXPECT_EQ(j, INT64_MIN);
        }
        {
            atomic_i64 i{INT64_MIN};
            i64 j = 0;
            EXPECT_FALSE(i.compare_exchange_strong(j, 1));
            EXPECT_EQ(j, INT64_MIN);
        }
        {
            atomic_i64 i{INT64_MIN};
            i64 j = INT64_MIN;
            EXPECT_TRUE(i.compare_exchange_weak(j, 1));
            EXPECT_EQ(j, INT64_MIN);
            EXPECT_EQ(i.load(), 1);
        }
        {
            atomic_i64 i{INT64_MIN};
            i64 j = INT64_MIN;
            EXPECT_TRUE(i.compare_exchange_strong(j, 1));
            EXPECT_EQ(j, INT64_MIN);
            EXPECT_EQ(i.load(), 1);
        }
    }
}

TEST(AtomicTest, LockFreeTest)
{
    {
        constexpr std::atomic<i64> standard{};
        constexpr rex::atomic<i64> implementation{};
        EXPECT_EQ(standard.is_lock_free(), implementation.is_lock_free());
        static_assert(decltype(standard)::is_always_lock_free == decltype(implementation)::is_always_lock_free);
    }

    {
        constexpr std::atomic<Sample128Bit_1> standard{};
        constexpr rex::atomic<Sample128Bit_1> implementation{};
        EXPECT_EQ(standard.is_lock_free(), implementation.is_lock_free());
        static_assert(decltype(standard)::is_always_lock_free == decltype(implementation)::is_always_lock_free);
    }
    {
        constexpr std::atomic<Sample128Bit_2> standard{};
        constexpr rex::atomic<Sample128Bit_2> implementation{};
        EXPECT_EQ(standard.is_lock_free(), implementation.is_lock_free());
        static_assert(decltype(standard)::is_always_lock_free == decltype(implementation)::is_always_lock_free);
    }
    {
        constexpr rex::atomic<Sample24Bit> bits24{};
        EXPECT_TRUE(bits24.is_lock_free());
        static_assert(decltype(bits24)::is_always_lock_free == false);
    }
    {
        constexpr std::atomic<Sample96Bits> standard{};
        constexpr rex::atomic<Sample96Bits> implementation{};
        EXPECT_EQ(standard.is_lock_free(), implementation.is_lock_free());
        static_assert(decltype(standard)::is_always_lock_free == decltype(implementation)::is_always_lock_free);
    }
}

TEST(AtomicTest, FetchAdd)
{
    using namespace rex;
    {
        atomic_i8 i{};
        EXPECT_EQ(i.fetch_add(1), 0);
        EXPECT_EQ(i.load(), 1);

        EXPECT_EQ(i.fetch_add(1), 1);
        EXPECT_EQ(i.load(), 2);
    }
    {
        atomic_i16 i{};
        EXPECT_EQ(i.fetch_add(1), 0);
        EXPECT_EQ(i.load(), 1);

        EXPECT_EQ(i.fetch_add(1), 1);
        EXPECT_EQ(i.load(), 2);
    }
    {
        atomic_i32 i{};
        EXPECT_EQ(i.fetch_add(1), 0);
        EXPECT_EQ(i.load(), 1);

        EXPECT_EQ(i.fetch_add(1), 1);
        EXPECT_EQ(i.load(), 2);
    }
    {
        atomic_i64 i{};
        EXPECT_EQ(i.fetch_add(1), 0);
        EXPECT_EQ(i.load(), 1);

        EXPECT_EQ(i.fetch_add(1), 1);
        EXPECT_EQ(i.load(), 2);
    }
}

TEST(AtomicTest, FetchSub)
{
    using namespace rex;
    {
        atomic_i8 i{};
        EXPECT_EQ(i.fetch_sub(1), 0);
        EXPECT_EQ(i.load(), -1);

        EXPECT_EQ(i.fetch_sub(1), -1);
        EXPECT_EQ(i.load(), -2);
    }
    {
        atomic_i16 i{};
        EXPECT_EQ(i.fetch_sub(1), 0);
        EXPECT_EQ(i.load(), -1);

        EXPECT_EQ(i.fetch_sub(1), -1);
        EXPECT_EQ(i.load(), -2);
    }
    {
        atomic_i32 i{};
        EXPECT_EQ(i.fetch_sub(1), 0);
        EXPECT_EQ(i.load(), -1);

        EXPECT_EQ(i.fetch_sub(1), -1);
        EXPECT_EQ(i.load(), -2);
    }
    {
        atomic_i64 i{};
        EXPECT_EQ(i.fetch_sub(1), 0);
        EXPECT_EQ(i.load(), -1);

        EXPECT_EQ(i.fetch_sub(1), -1);
        EXPECT_EQ(i.load(), -2);
    }
}

TEST(AtomicTest, FetchAnd)
{
    using namespace rex;
    {
        atomic_i8 i{0};
        EXPECT_EQ(i.fetch_and(1), 0);
        EXPECT_EQ(i.load(), 0);

        atomic_i8 j{1};
        EXPECT_EQ(j.fetch_and(1), 1);
        EXPECT_EQ(j.load(), 1);
    }
    {
        atomic_i16 i{5};
        EXPECT_EQ(i.fetch_and(1), 5);
        EXPECT_EQ(i.load(), 1);

        atomic_i16 j{2};
        EXPECT_EQ(j.fetch_and(1), 2);
        EXPECT_EQ(j.load(), 0);
    }
    {
        atomic_i32 i{0xF7};
        EXPECT_EQ(i.fetch_and(0x77), 0xF7);
        EXPECT_EQ(i.load(), 0x77);

        atomic_i32 j{1};
        EXPECT_EQ(j.fetch_and(1), 1);
        EXPECT_EQ(j.load(), 1);
    }
    {
        atomic_i64 i{0};
        EXPECT_EQ(i.fetch_and(1), 0);
        EXPECT_EQ(i.load(), 0);

        atomic_i64 j{1};
        EXPECT_EQ(j.fetch_and(1), 1);
        EXPECT_EQ(j.load(), 1);
    }
}

TEST(AtomicTest, FetchOr)
{
    using namespace rex;
    {
        atomic_i8 i{0};
        EXPECT_EQ(i.fetch_or(1), 0);
        EXPECT_EQ(i.load(), 1);

        atomic_i8 j{1};
        EXPECT_EQ(j.fetch_or(1), 1);
        EXPECT_EQ(j.load(), 1);
    }
    {
        atomic_i16 i{5};
        EXPECT_EQ(i.fetch_or(1), 5);
        EXPECT_EQ(i.load(), 5);

        atomic_i16 j{6};
        EXPECT_EQ(j.fetch_or(1), 6);
        EXPECT_EQ(j.load(), 7);
    }
    {
        atomic_i32 i{0xF7};
        EXPECT_EQ(i.fetch_or(0x77), 0xF7);
        EXPECT_EQ(i.load(), 0xF7);

        atomic_i32 j{0xFF};
        EXPECT_EQ(j.fetch_or(0x00), 0xFF);
        EXPECT_EQ(j.load(), 0xFF);
    }
    {
        atomic_i64 i{0};
        EXPECT_EQ(i.fetch_or(INT64_MIN), 0);
        EXPECT_EQ(i.load(), INT64_MIN);

        atomic_i64 j{1};
        EXPECT_EQ(j.fetch_or(1), 1);
        EXPECT_EQ(j.load(), 1);
    }
}

TEST(AtomicTest, FetchXor)
{
    using namespace rex;
    {
        atomic_i8 i{0};
        EXPECT_EQ(i.fetch_xor(1), 0);
        EXPECT_EQ(i.load(), 1);

        atomic_i8 j{1};
        EXPECT_EQ(j.fetch_xor(1), 1);
        EXPECT_EQ(j.load(), 0);
    }
    {
        atomic_i16 i{5};
        EXPECT_EQ(i.fetch_xor(1), 5);
        EXPECT_EQ(i.load(), 4);

        atomic_i16 j{2};
        EXPECT_EQ(j.fetch_xor(1), 2);
        EXPECT_EQ(j.load(), 3);
    }
    {
        atomic_i32 i{0xF7};
        EXPECT_EQ(i.fetch_xor(0x77), 0xF7);
        EXPECT_EQ(i.load(), 0x80);

        atomic_i32 j{1};
        EXPECT_EQ(j.fetch_and(1), 1);
        EXPECT_EQ(j.load(), 1);
    }
    {
        atomic_i64 i{0xFF};
        EXPECT_EQ(i.fetch_xor(0xFF), 0xFF);
        EXPECT_EQ(i.load(), 0);

        atomic_i64 j{0};
        EXPECT_EQ(j.fetch_xor(0xFF), 0);
        EXPECT_EQ(j.load(), 0xFF);
    }
}