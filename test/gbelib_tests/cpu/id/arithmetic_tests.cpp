#include "gtest/gtest.h"

#include "cpu/id/arithmetic.h"
#include "cpu/operation/operation.h"

using namespace id::arithmetic;

TEST(ArithmeticTest, Bulk)
{
  auto op = bulkArithmetic(OpcodeView(0x80));
  ASSERT_TRUE(op);
  EXPECT_TRUE(op->isComplete());
}

TEST(ArithmeticTest, Unimplemented) { EXPECT_THROW(auto op = bulkArithmetic(OpcodeView(0xC0)), std::logic_error); }

TEST(ArithmeticTest, SourceA)
{
  auto op = bulkArithmetic(OpcodeView(0x87));
  EXPECT_TRUE(op);
}

TEST(ArithmeticTest, SourceB)
{
  auto op = bulkArithmetic(OpcodeView(0x80));
  EXPECT_TRUE(op);
}

TEST(ArithmeticTest, SourceC)
{
  auto op = bulkArithmetic(OpcodeView(0x81));
  EXPECT_TRUE(op);
}

TEST(ArithmeticTest, SourceD)
{
  auto op = bulkArithmetic(OpcodeView(0x82));
  EXPECT_TRUE(op);
}

TEST(ArithmeticTest, SourceE)
{
  auto op = bulkArithmetic(OpcodeView(0x83));
  EXPECT_TRUE(op);
}

TEST(ArithmeticTest, SourceH)
{
  auto op = bulkArithmetic(OpcodeView(0x84));
  EXPECT_TRUE(op);
}

TEST(ArithmeticTest, SourceL)
{
  auto op = bulkArithmetic(OpcodeView(0x85));
  EXPECT_TRUE(op);
}
