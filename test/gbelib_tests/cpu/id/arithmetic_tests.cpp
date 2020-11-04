#include "gtest/gtest.h"

#include "cpu/id/arithmetic.h"
#include "cpu/operation/operation.h"

using namespace id::arithmetic;


TEST(ArithmeticTest, testBulk)
{
  auto op = bulkArithmetic(OpcodeView(0x80));
  ASSERT_TRUE(op);
  EXPECT_TRUE(op->isComplete());
}

TEST(ArithmeticTest, testUnimplemented)
{
  EXPECT_THROW(auto op = bulkArithmetic(OpcodeView(0xC0)), std::logic_error);
}

TEST(ArithmeticTest, testSourceA)
{
  auto op = bulkArithmetic(OpcodeView(0x87));
  EXPECT_TRUE(op);
}

TEST(ArithmeticTest, testSourceB)
{
  auto op = bulkArithmetic(OpcodeView(0x80));
  EXPECT_TRUE(op);
}

TEST(ArithmeticTest, testSourceC)
{
  auto op = bulkArithmetic(OpcodeView(0x81));
  EXPECT_TRUE(op);
}

TEST(ArithmeticTest, testSourceD)
{
  auto op = bulkArithmetic(OpcodeView(0x82));
  EXPECT_TRUE(op);
}

TEST(ArithmeticTest, testSourceE)
{
  auto op = bulkArithmetic(OpcodeView(0x83));
  EXPECT_TRUE(op);
}

TEST(ArithmeticTest, testSourceH)
{
  auto op = bulkArithmetic(OpcodeView(0x84));
  EXPECT_TRUE(op);
}

TEST(ArithmeticTest, testSourceL)
{
  auto op = bulkArithmetic(OpcodeView(0x85));
  EXPECT_TRUE(op);
}
