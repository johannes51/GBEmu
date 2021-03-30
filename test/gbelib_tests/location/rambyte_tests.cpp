#include "gtest/gtest.h"

#include "location/rambyte.h"

TEST(RamByteTest, Write)
{
  uint8_t buffer = 0;
  RamByte a(buffer);
  uint8_t value = 0x17;
  a.set(value);
  EXPECT_EQ(value, a.get());
}

TEST(RamByteTest, Read)
{
  uint8_t buffer = 0x2F;
  RamByte a(buffer);
  EXPECT_EQ(0x2F, a.get());
}
