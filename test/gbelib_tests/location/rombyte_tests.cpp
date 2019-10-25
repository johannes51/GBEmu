#include "gtest/gtest.h"

#include "location/rombyte.h"

TEST(RomByteTest, testRead) {
  uint8_t buffer = 0x4E;
  RomByte byte{buffer};
  EXPECT_EQ(0x4E, byte.get());
}

TEST(RomByteTest, testWrite) {
  uint8_t buffer = 0x4E;
  RomByte byte{buffer};
  EXPECT_ANY_THROW(byte.set(0));
}
