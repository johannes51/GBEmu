#include "gtest/gtest.h"

#include "mem/memoryarea.h"

TEST(MemoryAreaTest, testLessThan) {
  MemoryArea a{0, 16};
  MemoryArea b{0, 16};
  MemoryArea c{8, 16};
  MemoryArea d{8, 31};
  MemoryArea e{31, 48};
  MemoryArea f{32, 48};

  EXPECT_ANY_THROW(a < b);
  EXPECT_ANY_THROW(b < a);

  EXPECT_ANY_THROW(a < c);
  EXPECT_ANY_THROW(c < a);

  EXPECT_ANY_THROW(a < d);
  EXPECT_ANY_THROW(d < a);

  EXPECT_TRUE(a < e);
  EXPECT_FALSE(e < a);

  EXPECT_ANY_THROW(c < d);
  EXPECT_ANY_THROW(d < c);

  EXPECT_ANY_THROW(d < e);
  EXPECT_ANY_THROW(e < d);

  EXPECT_TRUE(d < f);
  EXPECT_FALSE(f < d);
}

