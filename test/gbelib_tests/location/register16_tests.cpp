#include "gtest/gtest.h"

#include "mem/registers/register16.h"

TEST(Register16Test, ReadWrite)
{
  uint16_t b { 0xFFFFU };
  Register16 r1 { b };
  Register16 r2 { b };

  EXPECT_EQ(0xFFFFU, r1.get());
  EXPECT_EQ(0xFFFFU, r2.get());

  r2.set(0xEEEEU);

  EXPECT_EQ(0xEEEEU, r1.get());
  EXPECT_EQ(0xEEEEU, r2.get());
}
