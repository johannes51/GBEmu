#include "gtest/gtest.h"

#include "cpu/id/loads.h"
#include "cpu/operation/operation.h"

TEST(LoadsTest, testLoad)
{
  EXPECT_ANY_THROW(auto op = id::loads::bulkLoad(OpcodeView(0x3F))); // TODO: implement
  //  ASSERT_TRUE(op);
  //  EXPECT_NO_THROW(op->isDone());
}
