#include "gtest/gtest.h"

#include "cpu/registers/register8.h"

TEST(Register8Test, ReadWrite)
{
  uint16_t b { 0xFFFFU };
  Register8 r1 { b, false };
  Register8 r2 { b, true };

  EXPECT_EQ(0xFFU, r1.get());
  EXPECT_EQ(0xFFU, r2.get());

  r1 = 0x42U;

  EXPECT_EQ(0x42U, r1.get());
  EXPECT_EQ(0xFFU, r2.get());

  r2 = 0x42U;

  EXPECT_EQ(0x42U, r1.get());
  EXPECT_EQ(0x42U, r2.get());
}
