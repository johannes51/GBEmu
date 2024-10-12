#include "gtest/gtest.h"

#include "location/zerolocation.h"

TEST(ZeroTest, Location)
{
  ZeroLocation zero {};
  EXPECT_EQ(0x0, zero.getByte());
  EXPECT_NO_THROW(zero = uint8_t(0x42));
  EXPECT_EQ(0x0, zero.getByte());
  EXPECT_NO_THROW(zero = uint16_t(0xAA42));
  EXPECT_EQ(0x0, zero.getWord());
}
