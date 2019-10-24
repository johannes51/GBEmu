#include "gtest/gtest.h"

#include "mem/memoryarea.h"

TEST(MemoryAreaTest, testLessThan) {
  MemoryArea a{0, 16};
  MemoryArea b{0, 16};
  MemoryArea c{8, 16};
  MemoryArea d{8, 31};

  EXPECT_FALSE(a < b);
  EXPECT_FALSE(b < a);

  EXPECT_TRUE(a < c);
  EXPECT_FALSE(c < a);

  EXPECT_TRUE(a < d);
  EXPECT_FALSE(d < a);
}

