#include "gtest/gtest.h"

#include "cpu/id/loads.h"
#include "cpu/operation/operation.h"

TEST(LoadsTest, Load)
{
  auto op = id::loads::bulkLoad(OpcodeView(0x3A));
  ASSERT_TRUE(op);
  EXPECT_TRUE(op->isComplete());
}
