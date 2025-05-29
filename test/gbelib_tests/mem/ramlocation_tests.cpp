#include "gtest/gtest.h"

#include "mem/ram/ramlocation.h"

TEST(RamLocationTest, ReadWrite)
{
  uint8_t b { 0U };
  RamLocation a { b };
  uint8_t value = 0x17;
  EXPECT_NE(value, a.get());
  a = value;
  EXPECT_EQ(value, a.get());
}
