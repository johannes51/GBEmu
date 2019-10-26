#include "gtest/gtest.h"

#include "cpu/id/arithmetic.h"
#include "cpu/operation/operation.h"

using namespace id::arithmetic;

TEST(ArithmeticTest, testBulk)
{
  auto op = bulkArithmetic(OpcodeView(0x80));
  ASSERT_TRUE(op);
  EXPECT_NO_THROW(op->isDone());
}
