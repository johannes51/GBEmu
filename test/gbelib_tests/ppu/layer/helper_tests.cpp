#include "gtest/gtest.h"

#include "ppu/layer/helper.h"

TEST(HelperTests, ZeroZero)
{
  auto result = decomposePos(0, 0);

  EXPECT_EQ(result.first.x, 0);
  EXPECT_EQ(result.first.y, 0);
  EXPECT_EQ(result.second.x, 0);
  EXPECT_EQ(result.second.y, 0);
}

// TODO: write more tests
