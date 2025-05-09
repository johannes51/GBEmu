#include "gtest/gtest.h"

#include "mock/testbank.h"

#include "location/ramlocation.h"

TEST(RamLocationTest, ReadWrite)
{
  TestBank b { { 0, 2 } };
  RamLocation a { b, 0 };
  uint8_t value = 0x17;
  a = value;
  EXPECT_EQ(value, a.get());
}
