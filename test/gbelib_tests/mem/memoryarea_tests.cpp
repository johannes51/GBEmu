#include "gtest/gtest.h"

#include "mem/mem_defines.h"

TEST(MemoryAreaTest, LessThan)
{
  MemoryArea a { 0x0U, 0xFU };
  MemoryArea b { 0x0U, 0xFU };
  MemoryArea c { 0x8U, 0xFU };
  MemoryArea d { 8, 31 };

  EXPECT_FALSE(a < b);
  EXPECT_FALSE(b < a);

  EXPECT_TRUE(a < c);
  EXPECT_FALSE(c < a);

  EXPECT_TRUE(a < d);
  EXPECT_FALSE(d < a);
}

TEST(MemoryAreaTest, Equals)
{
  MemoryArea a { 0x0U, 0xFU };
  MemoryArea b { 0x0U, 0xFU };
  MemoryArea c { 0x8U, 0xFU };

  EXPECT_TRUE(a == b);
  EXPECT_TRUE(b == a);

  EXPECT_FALSE(a == c);
  EXPECT_FALSE(c == a);
}

TEST(MemoryAreaTest, Size)
{
  MemoryArea a { 0x0U, 0xFU };
  MemoryArea b { 0x0U, 0xFU };
  MemoryArea c { 0x8U, 0xFU };

  EXPECT_EQ(16U, a.size());
  EXPECT_EQ(16U, b.size());
  EXPECT_EQ(8U, c.size());
}
