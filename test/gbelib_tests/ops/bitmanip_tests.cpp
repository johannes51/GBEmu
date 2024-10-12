#include "gtest/gtest.h"

#include "ops/bitmanip.h"

#include "location/variablelocation.h"

TEST(BitmanipTest, Bit)
{
  auto l = variableLocation(uint8_t { 0b00010010U });

  auto res = ops::bit(*l, 4U);

  auto expected = ops::OpResult { ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Set,
    ops::FlagResult::NoChange };
  EXPECT_EQ(expected, res);

  res = ops::bit(*l, 0U);

  expected
      = ops::OpResult { ops::FlagResult::Set, ops::FlagResult::Reset, ops::FlagResult::Set, ops::FlagResult::NoChange };
  EXPECT_EQ(expected, res);
}

TEST(BitmanipTest, Set)
{
  auto l = variableLocation(uint8_t { 0b00010010U });

  auto res = ops::set(*l, 0U);

  auto expected = ops::OpResult { ops::FlagResult::NoChange, ops::FlagResult::NoChange, ops::FlagResult::NoChange,
    ops::FlagResult::NoChange };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b00010011U, l->getByte());

  res = ops::set(*l, 4U);

  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b00010011U, l->getByte());
}

TEST(BitmanipTest, Reset)
{
  auto l = variableLocation(uint8_t { 0b00010010U });

  auto res = ops::reset(*l, 4U);

  auto expected = ops::OpResult { ops::FlagResult::NoChange, ops::FlagResult::NoChange, ops::FlagResult::NoChange,
    ops::FlagResult::NoChange };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b00000010U, l->getByte());

  res = ops::reset(*l, 0U);

  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b00000010U, l->getByte());
}