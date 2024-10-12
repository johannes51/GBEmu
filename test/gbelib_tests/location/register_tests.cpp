#include "gtest/gtest.h"

#include "location/register.h"

TEST(RegisterTest, ReadWrite)
{
  uint16_t b { 0xFFFFU };
  Register r1 { b, false };
  Register r2 { b };

  EXPECT_EQ(&r1.getReference() + 1U, &r2.getReference());

  EXPECT_EQ(0xFFU, r1.getByte());
  EXPECT_EQ(0xFFU, r2.getByte());
  EXPECT_EQ(0xFFFFU, r1.getWord());

  r1 = uint8_t { 0x42U };

  EXPECT_EQ(0x42U, r1.getByte());
  EXPECT_EQ(0xFFU, r2.getByte());
  EXPECT_EQ(0xFF42U, r1.getWord());

  r2 = uint8_t { 0x42U };

  EXPECT_EQ(0x42U, r1.getByte());
  EXPECT_EQ(0x42U, r2.getByte());
  EXPECT_EQ(0x4242U, r1.getWord());

  r2 = uint16_t { 0xEEEEU };

  EXPECT_EQ(0xEEU, r1.getByte());
  EXPECT_EQ(0xEEU, r2.getByte());
  EXPECT_EQ(0xEEEEU, r1.getWord());
}
