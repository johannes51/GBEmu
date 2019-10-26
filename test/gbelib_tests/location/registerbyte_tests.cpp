#include "gtest/gtest.h"

#include "location/registerbyte.h"

TEST(RegisterByteTest, testWrite)
{
  uint8_t buffer;
  RegisterByte a(buffer);
  uint8_t value = 0x42;
  a.set(value);
  EXPECT_EQ(value, a.get());
}

TEST(RegisterByteTest, testRead)
{
  uint8_t buffer = 0x4E;
  RegisterByte byte { buffer };
  EXPECT_EQ(0x4E, byte.get());
}
