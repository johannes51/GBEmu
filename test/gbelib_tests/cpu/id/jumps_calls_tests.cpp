#include "gtest/gtest.h"

#include "cpu/id/jumps_calls.h"
#include "cpu/operation/operation.h"

using namespace id::jumps_calls;

TEST(ArithmeticTest, testDirect)
{
  auto op = jumpDirect();
  ASSERT_TRUE(op);
  EXPECT_FALSE(op->isComplete());
}
