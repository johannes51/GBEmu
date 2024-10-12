#include "gtest/gtest.h"

#include "location/location.h"
#include "ops/logic.h"

#include "location/variablelocation.h"

TEST(LogicTest, And)
{
  auto d = variableLocation(uint8_t { 0b00101110U });
  auto s = variableLocation(uint8_t { 0b01011010U });

  auto res = ops::andF(*d, *s);

  auto expected = ops::OpResult { ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Reset,
    ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b00001010U, d->getByte());

  *s = uint8_t { 0b11110101U };

  res = ops::xorF(*d, *d);

  expected
      = ops::OpResult { ops::FlagResult::Set, ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0x00U, d->getByte());
}

TEST(LogicTest, Or)
{
  auto d = variableLocation(uint8_t { 0b00101110U });
  auto s = variableLocation(uint8_t { 0b01011010U });

  auto res = ops::orF(*d, *s);

  auto expected = ops::OpResult { ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Reset,
    ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b01111110U, d->getByte());

  *d = uint8_t { 0b00000000U };
  *s = uint8_t { 0b00000000U };

  res = ops::orF(*d, *d);

  expected
      = ops::OpResult { ops::FlagResult::Set, ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0x00U, d->getByte());
}

TEST(LogicTest, Xor)
{
  auto d = variableLocation(uint8_t { 0x3CU });
  auto s = variableLocation(uint8_t { 0xF1U });

  auto res = ops::xorF(*d, *s);

  auto expected = ops::OpResult { ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Reset,
    ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0xCDU, d->getByte());

  res = ops::xorF(*d, *d);

  expected
      = ops::OpResult { ops::FlagResult::Set, ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0x00U, d->getByte());
}

TEST(LogicTest, Cp)
{
  auto a = variableLocation(uint8_t { 0b10001000U });
  auto n = variableLocation(uint8_t { 0b00001100U });

  auto res = ops::cpF(*a, *n);

  auto expected
      = ops::OpResult { ops::FlagResult::Reset, ops::FlagResult::Set, ops::FlagResult::Set, ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b10001000U, a->getByte());

  *n = uint8_t { 0b11001000U };

  res = ops::cpF(*a, *n);

  expected
      = ops::OpResult { ops::FlagResult::Reset, ops::FlagResult::Set, ops::FlagResult::Reset, ops::FlagResult::Set };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b10001000U, a->getByte());

  *n = uint8_t { 0b10001000U };

  res = ops::cpF(*a, *a);

  expected
      = ops::OpResult { ops::FlagResult::Set, ops::FlagResult::Set, ops::FlagResult::Reset, ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b10001000U, a->getByte());
}
