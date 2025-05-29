#include "gtest/gtest.h"

#include "mem/rest/zerolocation.h"

TEST(ZeroTest, Location8)
{
  ZeroLocation zero {};
  EXPECT_EQ(0x0, zero.get());
  EXPECT_NO_THROW(zero = 0x42);
  EXPECT_EQ(0x0, zero.get());
}
