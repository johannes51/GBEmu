#include "gtest/gtest.h"

#include "cpu/operation/operation.h"
#include "location/location.h"
#include "location/variablebyte.h"

#include "cpu/id/bytearithmeticdecoder.h"

class ByteArithmeticTest : public ::testing::Test {
public:
  ByteArithmeticTest()
      : b()
  {
  }

protected:
  ByteArithmeticDecoder b;
};

TEST_F(ByteArithmeticTest, Bulk)
{
  auto op = b.decode(variableLocation(0x80));
  ASSERT_TRUE(op);
  EXPECT_TRUE(op->isComplete());
}

TEST_F(ByteArithmeticTest, Unimplemented)
{
  EXPECT_THROW(auto op = b.decode(variableLocation(0xC0)), std::logic_error);
}

TEST_F(ByteArithmeticTest, SourceA)
{
  auto op = b.decode(variableLocation(0x87));
  EXPECT_TRUE(op);
}

TEST_F(ByteArithmeticTest, SourceB)
{
  auto op = b.decode(variableLocation(0x80));
  EXPECT_TRUE(op);
}

TEST_F(ByteArithmeticTest, SourceC)
{
  auto op = b.decode(variableLocation(0x81));
  EXPECT_TRUE(op);
}

TEST_F(ByteArithmeticTest, SourceD)
{
  auto op = b.decode(variableLocation(0x82));
  EXPECT_TRUE(op);
}

TEST_F(ByteArithmeticTest, SourceE)
{
  auto op = b.decode(variableLocation(0x83));
  EXPECT_TRUE(op);
}

TEST_F(ByteArithmeticTest, SourceH)
{
  auto op = b.decode(variableLocation(0x84));
  EXPECT_TRUE(op);
}

TEST_F(ByteArithmeticTest, SourceL)
{
  auto op = b.decode(variableLocation(0x85));
  EXPECT_TRUE(op);
}
