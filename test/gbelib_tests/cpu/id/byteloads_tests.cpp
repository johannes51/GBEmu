#include "gtest/gtest.h"

#include "cpu/operation/operation.h"
#include "location/location.h"
#include "location/variablelocation.h"

#include "cpu/id/byteloadsdecoder.h"

class ByteLoadsTest : public ::testing::Test {
public:
  ByteLoadsTest()
      : d()
  {
  }

protected:
  ByteLoadsDecoder d;
};

TEST_F(ByteLoadsTest, BulkLoad1)
{
  auto op = d.decode(*variableLocation(uint8_t(0x42)));
  ASSERT_TRUE(op);
  EXPECT_TRUE(op->isComplete());
}

TEST_F(ByteLoadsTest, BulkLoad2)
{
  auto op = d.decode(*variableLocation(uint8_t(0x69)));
  ASSERT_TRUE(op);
  EXPECT_TRUE(op->isComplete());
}

TEST_F(ByteLoadsTest, ImmediateLoad)
{
  auto op = d.decode(*variableLocation(uint8_t(0x1E)));
  ASSERT_TRUE(op);
  EXPECT_FALSE(op->isComplete());
}

TEST_F(ByteLoadsTest, RegInLoad)
{
  auto op = d.decode(*variableLocation(uint8_t(0x3A)));
  ASSERT_TRUE(op);
  EXPECT_TRUE(op->isComplete());
}

TEST_F(ByteLoadsTest, OddballLoad)
{
  auto op = d.decode(*variableLocation(uint8_t(0xEA)));
  ASSERT_TRUE(op);
  EXPECT_FALSE(op->isComplete());
}
