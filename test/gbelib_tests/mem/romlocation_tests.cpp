#include "gtest/gtest.h"

#include "mem/rom/romlocation.h"

TEST(RomLocationTest, Read)
{
  uint8_t b { 0xFU };
  RomLocation a { b };

  EXPECT_EQ(0xFU, a.get());
}

TEST(RomLocationTest, Write)
{
  uint8_t b { 0xFU };
  RomLocation a { b };

  EXPECT_NO_THROW(a = 0U);
  EXPECT_EQ(0xFU, a.get());
}
