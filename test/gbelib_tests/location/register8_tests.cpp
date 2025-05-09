#include "gtest/gtest.h"

#include "location/register8.h"

TEST(Register8Test, ReadWrite)
{
  uint16_t b { 0xFFFFU };
  Register8 r1 { b, false };
  Register8 r2 { b };

  EXPECT_EQ(&r1.getReference() + 1U, &r2.getReference());

  EXPECT_EQ(0xFFU, r1.get());
  EXPECT_EQ(0xFFU, r2.get());

  r1 = uint8_t { 0x42U };

  EXPECT_EQ(0x42U, r1.get());
  EXPECT_EQ(0xFFU, r2.get());

  r2 = uint8_t { 0x42U };

  EXPECT_EQ(0x42U, r1.get());
  EXPECT_EQ(0x42U, r2.get());
}
