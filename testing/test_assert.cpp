#include <gtest/gtest.h>
#include <rex/assert.hpp>

TEST(RexAssert, AssertionMacros)
{
    EXPECT_DEATH(REX_ASSERT(false), "");
    EXPECT_DEATH(REX_ASSERT_MSG(false, ""), "");
}