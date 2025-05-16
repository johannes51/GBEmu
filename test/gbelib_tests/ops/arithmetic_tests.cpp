#include "gtest/gtest.h"

#include "mem/location8.h"
#include "ops/arithmetic.h"

#include "mem/rest/variablelocation.h"

TEST(ArithmeticTest, Increment8)
{
  auto l = variableLocation(uint8_t { 0b00001101U });

  auto res = ops::increment(l);

  auto expected = ops::OpResult { .z = ops::FlagResult::Reset,
    .n = ops::FlagResult::Reset,
    .h = ops::FlagResult::Reset,
    .c = ops::FlagResult::NoChange };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b00001110U, l.get());

  res = ops::increment(l);
  res = ops::increment(l);

  expected = ops::OpResult {
    .z = ops::FlagResult::Reset, .n = ops::FlagResult::Reset, .h = ops::FlagResult::Set, .c = ops::FlagResult::NoChange
  };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b00010000U, l.get());

  l = uint8_t { 0b11111111U };

  res = ops::increment(l);

  expected = ops::OpResult {
    .z = ops::FlagResult::Set, .n = ops::FlagResult::Reset, .h = ops::FlagResult::Set, .c = ops::FlagResult::NoChange
  };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b00000000, l.get());
}

TEST(ArithmeticTest, Increment16)
{
  auto l = variableLocation(uint16_t { 0xFFFEU });

  auto res = ops::increment(l);

  auto expected = ops::OpResult { .z = ops::FlagResult::NoChange,
    .n = ops::FlagResult::NoChange,
    .h = ops::FlagResult::NoChange,
    .c = ops::FlagResult::NoChange };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0xFFFFU, l.get());

  res = ops::increment(l);

  EXPECT_EQ(expected, res);
  EXPECT_EQ(0x0000U, l.get());
}

TEST(ArithmeticTest, Add8)
{
  auto lA = variableLocation(uint8_t { 0b00001100U });
  auto lB = variableLocation(uint8_t { 0b00001010U });

  auto res = ops::add(lA, lB);

  auto expected = ops::OpResult {
    .z = ops::FlagResult::Reset, .n = ops::FlagResult::Reset, .h = ops::FlagResult::Set, .c = ops::FlagResult::Reset
  };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b00010110U, lA.get());

  lB = uint8_t { 0b11110000U };

  res = ops::add(lA, lB);

  expected = ops::OpResult {
    .z = ops::FlagResult::Reset, .n = ops::FlagResult::Reset, .h = ops::FlagResult::Reset, .c = ops::FlagResult::Set
  };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b00000110U, lA.get());

  lB = uint8_t { 0b11111010U };

  res = ops::add(lA, lB);

  expected = ops::OpResult {
    .z = ops::FlagResult::Set, .n = ops::FlagResult::Reset, .h = ops::FlagResult::Set, .c = ops::FlagResult::Set
  };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b00000000U, lA.get());
}

TEST(ArithmeticTest, Add16)
{
  auto lA = variableLocation(uint16_t { 0b0001010000110101U });
  auto lB = variableLocation(uint16_t { 0b1100011110100010U });

  auto res = ops::add(lA, lB);

  auto expected = ops::OpResult { .z = ops::FlagResult::NoChange,
    .n = ops::FlagResult::Reset,
    .h = ops::FlagResult::Reset,
    .c = ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b1101101111010111U, lA.get());

  lA = uint16_t { 0b1000100000000000U };
  lB = uint16_t { 0b1000100000000000U };

  res = ops::add(lA, lB);

  expected = ops::OpResult {
    .z = ops::FlagResult::NoChange, .n = ops::FlagResult::Reset, .h = ops::FlagResult::Set, .c = ops::FlagResult::Set
  };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b0001000000000000U, lA.get());
}

TEST(ArithmeticTest, AddSigned)
{
  auto lA = variableLocation(uint16_t { 0xFF04U });
  auto opSigned = int8_t { -5 };
  auto lB = variableLocation(*reinterpret_cast<uint8_t*>(&opSigned)); // NOLINT

  auto res = ops::addSigned(lA, lB.get());

  auto expected = ops::OpResult {
    .z = ops::FlagResult::Reset, .n = ops::FlagResult::Reset, .h = ops::FlagResult::Reset, .c = ops::FlagResult::Reset
  };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0xFEFFU, lA.get());

  opSigned = int8_t { -1 };
  lB = variableLocation(*reinterpret_cast<uint8_t*>(&opSigned)); // NOLINT

  res = ops::addSigned(lA, lB.get());

  expected = ops::OpResult {
    .z = ops::FlagResult::Reset, .n = ops::FlagResult::Reset, .h = ops::FlagResult::Set, .c = ops::FlagResult::Set
  };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0xFEFEU, lA.get());
}

TEST(ArithmeticTest, Sub)
{
  auto lA = variableLocation(uint8_t { 0b10000000U });
  auto lB = variableLocation(uint8_t { 0b10000000U });

  auto res = ops::sub(lA, lB);

  auto expected = ops::OpResult {
    .z = ops::FlagResult::Set, .n = ops::FlagResult::Set, .h = ops::FlagResult::Reset, .c = ops::FlagResult::Reset
  };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b00000000U, lA.get());

  lB = uint8_t { 0b00000001U };

  res = ops::sub(lA, lB);

  expected = ops::OpResult {
    .z = ops::FlagResult::Reset, .n = ops::FlagResult::Set, .h = ops::FlagResult::Set, .c = ops::FlagResult::Set
  };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b11111111U, lA.get());
}

TEST(ArithmeticTest, Complement)
{
  auto l = variableLocation(uint8_t { 0b01010101U });

  auto res = ops::complement(l);

  auto expected = ops::OpResult {
    .z = ops::FlagResult::NoChange, .n = ops::FlagResult::Set, .h = ops::FlagResult::Set, .c = ops::FlagResult::NoChange
  };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b10101010U, l.get());
}

TEST(ArithmeticTest, DecimalAdjust)
{
  auto l = variableLocation(uint8_t { 00U });

  auto res = ops::decimalAdjust(l, false, false, false);

  auto expected = ops::OpResult {
    .z = ops::FlagResult::Set, .n = ops::FlagResult::NoChange, .h = ops::FlagResult::Reset, .c = ops::FlagResult::Reset
  };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b00000000U, l.get());

  l = uint8_t { 19U };

  res = ops::decimalAdjust(l, false, false, false);

  expected = ops::OpResult { .z = ops::FlagResult::Reset,
    .n = ops::FlagResult::NoChange,
    .h = ops::FlagResult::Reset,
    .c = ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0x13U, l.get());

  l = uint8_t { 28U };

  res = ops::decimalAdjust(l, false, false, false);

  expected = ops::OpResult { .z = ops::FlagResult::Reset,
    .n = ops::FlagResult::NoChange,
    .h = ops::FlagResult::Reset,
    .c = ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0x22U, l.get());

  l = uint8_t { 37U };

  res = ops::decimalAdjust(l, false, false, false);

  expected = ops::OpResult { .z = ops::FlagResult::Reset,
    .n = ops::FlagResult::NoChange,
    .h = ops::FlagResult::Reset,
    .c = ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0x25U, l.get());

  l = uint8_t { 46U };

  res = ops::decimalAdjust(l, false, false, false);

  expected = ops::OpResult { .z = ops::FlagResult::Reset,
    .n = ops::FlagResult::NoChange,
    .h = ops::FlagResult::Reset,
    .c = ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0x34U, l.get());

  l = uint8_t { 55U };

  res = ops::decimalAdjust(l, false, false, false);

  expected = ops::OpResult { .z = ops::FlagResult::Reset,
    .n = ops::FlagResult::NoChange,
    .h = ops::FlagResult::Reset,
    .c = ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0x37U, l.get());

  l = uint8_t { 64U };

  res = ops::decimalAdjust(l, false, false, false);

  expected = ops::OpResult { .z = ops::FlagResult::Reset,
    .n = ops::FlagResult::NoChange,
    .h = ops::FlagResult::Reset,
    .c = ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0x40U, l.get());

  l = uint8_t { 73U };

  res = ops::decimalAdjust(l, false, false, false);

  expected = ops::OpResult { .z = ops::FlagResult::Reset,
    .n = ops::FlagResult::NoChange,
    .h = ops::FlagResult::Reset,
    .c = ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0x49U, l.get());

  l = uint8_t { 82U };

  res = ops::decimalAdjust(l, false, false, false);

  expected = ops::OpResult { .z = ops::FlagResult::Reset,
    .n = ops::FlagResult::NoChange,
    .h = ops::FlagResult::Reset,
    .c = ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0x52U, l.get());

  l = uint8_t { 91U };

  res = ops::decimalAdjust(l, false, false, false);

  expected = ops::OpResult { .z = ops::FlagResult::Reset,
    .n = ops::FlagResult::NoChange,
    .h = ops::FlagResult::Reset,
    .c = ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0x61U, l.get());
}
