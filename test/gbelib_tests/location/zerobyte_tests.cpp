#include "gtest/gtest.h"

#include "location/zerobyte.h"

TEST(ZeroTest, Byte)
{
  ZeroByte byte {};
  EXPECT_EQ(0x0, byte.get());
  EXPECT_NO_THROW(byte.set(0x42));
  EXPECT_EQ(0x0, byte.get());
}
