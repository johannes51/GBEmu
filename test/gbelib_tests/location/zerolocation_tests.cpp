#include "gtest/gtest.h"

#include "mem/rest/zerolocation.h"

TEST(ZeroTest, Location8)
{
  ZeroByteLocation zero {};
  EXPECT_EQ(0x0, zero.get());
  EXPECT_NO_THROW(zero.set(0x42));
  EXPECT_EQ(0x0, zero.get());
}

TEST(ZeroTest, Location16)
{
  ZeroWordLocation zero {};
  EXPECT_EQ(0x0, zero.get());
  EXPECT_NO_THROW(zero.set(0x42));
  EXPECT_EQ(0x0, zero.get());
  EXPECT_NO_THROW(zero.set(0xAA42));
  EXPECT_EQ(0x0, zero.get());
}
