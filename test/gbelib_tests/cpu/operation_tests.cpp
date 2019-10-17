#include "gtest/gtest.h"

#include "cpu/operation.h"


using namespace std;

TEST(OperationTest, testOp)
{
  auto op = Operation(0xFA);
  ASSERT_EQ(0xF, op.upperNibble());
  ASSERT_EQ(0xA, op.lowerNibble());
}


