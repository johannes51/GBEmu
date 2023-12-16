#include "gtest/gtest.h"

#include "location/rombyte.h"

TEST(RomByteTest, Read)
{
  uint8_t buffer = 0x4E;
  const RomByte byte { buffer };
  EXPECT_EQ(0x4E, byte.get());
}

TEST(RomByteTest, Write)
{
  uint8_t buffer = 0x4E;
  RomByte byte { buffer };
  EXPECT_ANY_THROW(byte.set(0));
}
