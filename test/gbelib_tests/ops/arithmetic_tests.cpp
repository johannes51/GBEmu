#include "gtest/gtest.h"

#include "location/location.h"
#include "ops/arithmetic.h"

#include "location/variablelocation.h"

TEST(ArithmeticTest, Increment8)
{
  auto l = variableLocation(uint8_t { 0b00001101U });

  auto res = ops::increment<uint8_t>(*l);

  auto expected = ops::OpResult { ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Reset,
    ops::FlagResult::NoChange };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b00001110U, l->getByte());

  res = ops::increment<uint8_t>(*l);
  res = ops::increment<uint8_t>(*l);

  expected = ops::OpResult { ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Set,
    ops::FlagResult::NoChange };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b00010000U, l->getByte());

  *l = uint8_t { 0b11111111U };

  res = ops::increment<uint8_t>(*l);

  expected
      = ops::OpResult { ops::FlagResult::Set, ops::FlagResult::Reset, ops::FlagResult::Set, ops::FlagResult::NoChange };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b00000000, l->getByte());
}

TEST(ArithmeticTest, Increment16)
{
  auto l = variableLocation(uint16_t { 0xFFFEU });

  auto res = ops::increment<uint16_t>(*l);

  auto expected = ops::OpResult { ops::FlagResult::NoChange, ops::FlagResult::NoChange, ops::FlagResult::NoChange,
    ops::FlagResult::NoChange };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0xFFFFU, l->getWord());

  res = ops::increment<uint16_t>(*l);

  EXPECT_EQ(expected, res);
  EXPECT_EQ(0x0000U, l->getWord());
}

TEST(ArithmeticTest, Add8)
{
  auto lA = variableLocation(uint8_t { 0b00001100U });
  auto lB = variableLocation(uint8_t { 0b00001010U });

  auto res = ops::add<uint8_t>(*lA, *lB);

  auto expected
      = ops::OpResult { ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Set, ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b00010110U, lA->getByte());

  *lB = uint8_t { 0b11110000U };

  res = ops::add<uint8_t>(*lA, *lB);

  expected
      = ops::OpResult { ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Set };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b00000110U, lA->getByte());

  *lB = uint8_t { 0b11111010U };

  res = ops::add<uint8_t>(*lA, *lB);

  expected = ops::OpResult { ops::FlagResult::Set, ops::FlagResult::Reset, ops::FlagResult::Set, ops::FlagResult::Set };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b00000000U, lA->getByte());
}

TEST(ArithmeticTest, Add16)
{
  auto lA = variableLocation(uint16_t { 0b0001010000110101U });
  auto lB = variableLocation(uint16_t { 0b1100011110100010U });

  auto res = ops::add<uint16_t>(*lA, *lB);

  auto expected = ops::OpResult { ops::FlagResult::NoChange, ops::FlagResult::Reset, ops::FlagResult::Reset,
    ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b1101101111010111U, lA->getWord());

  *lA = uint16_t { 0b1000100000000000U };
  *lB = uint16_t { 0b1000100000000000U };

  res = ops::add<uint16_t>(*lA, *lB);

  expected
      = ops::OpResult { ops::FlagResult::NoChange, ops::FlagResult::Reset, ops::FlagResult::Set, ops::FlagResult::Set };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b0001000000000000U, lA->getWord());
}

TEST(ArithmeticTest, AddSigned)
{
  auto lA = variableLocation(uint16_t { 0xFF04U });
  auto opSigned = int8_t { -5 };
  auto lB = variableLocation(*reinterpret_cast<uint8_t*>(&opSigned)); // NOLINT

  auto res = ops::addSigned(*lA, *lB);

  auto expected
      = ops::OpResult { ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Set, ops::FlagResult::Set };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0xFEFFU, lA->getWord());

  opSigned = int8_t { -1 };
  *lB = *reinterpret_cast<uint8_t*>(&opSigned); // NOLINT

  res = ops::addSigned(*lA, *lB);

  expected = ops::OpResult { ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Reset,
    ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0xFEFEU, lA->getWord());
}

TEST(ArithmeticTest, Sub)
{
  auto lA = variableLocation(uint8_t { 0b10000000U });
  auto lB = variableLocation(uint8_t { 0b10000000U });

  auto res = ops::sub(*lA, *lB);

  auto expected
      = ops::OpResult { ops::FlagResult::Set, ops::FlagResult::Set, ops::FlagResult::Set, ops::FlagResult::Set };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b00000000U, lA->getByte());

  *lB = uint8_t { 0b00000001U };

  res = ops::sub(*lA, *lB);

  expected
      = ops::OpResult { ops::FlagResult::Reset, ops::FlagResult::Set, ops::FlagResult::Reset, ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b11111111U, lA->getWord());
}

TEST(ArithmeticTest, Complement)
{
  auto l = variableLocation(uint8_t { 0b01010101U });

  auto res = ops::complement(*l);

  auto expected = ops::OpResult { ops::FlagResult::NoChange, ops::FlagResult::Set, ops::FlagResult::Set,
    ops::FlagResult::NoChange };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b10101010U, l->getByte());
}

TEST(ArithmeticTest, DecimalAdjust)
{
  auto l = variableLocation(uint8_t { 00U });

  auto res = ops::decimalAdjust(*l);

  auto expected = ops::OpResult { ops::FlagResult::Set, ops::FlagResult::NoChange, ops::FlagResult::Reset,
    ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b00000000U, l->getByte());

  *l = uint8_t { 19U };

  res = ops::decimalAdjust(*l);

  expected = ops::OpResult { ops::FlagResult::Reset, ops::FlagResult::NoChange, ops::FlagResult::Reset,
    ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b00011001U, l->getByte());

  *l = uint8_t { 28U };

  res = ops::decimalAdjust(*l);

  expected = ops::OpResult { ops::FlagResult::Reset, ops::FlagResult::NoChange, ops::FlagResult::Reset,
    ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b00101000U, l->getByte());

  *l = uint8_t { 37U };

  res = ops::decimalAdjust(*l);

  expected = ops::OpResult { ops::FlagResult::Reset, ops::FlagResult::NoChange, ops::FlagResult::Reset,
    ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b00110111U, l->getByte());

  *l = uint8_t { 46U };

  res = ops::decimalAdjust(*l);

  expected = ops::OpResult { ops::FlagResult::Reset, ops::FlagResult::NoChange, ops::FlagResult::Reset,
    ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b01000110U, l->getByte());

  *l = uint8_t { 55U };

  res = ops::decimalAdjust(*l);

  expected = ops::OpResult { ops::FlagResult::Reset, ops::FlagResult::NoChange, ops::FlagResult::Reset,
    ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b01010101U, l->getByte());

  *l = uint8_t { 64U };

  res = ops::decimalAdjust(*l);

  expected = ops::OpResult { ops::FlagResult::Reset, ops::FlagResult::NoChange, ops::FlagResult::Reset,
    ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b01100100U, l->getByte());

  *l = uint8_t { 73U };

  res = ops::decimalAdjust(*l);

  expected = ops::OpResult { ops::FlagResult::Reset, ops::FlagResult::NoChange, ops::FlagResult::Reset,
    ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b01110011U, l->getByte());

  *l = uint8_t { 82U };

  res = ops::decimalAdjust(*l);

  expected = ops::OpResult { ops::FlagResult::Reset, ops::FlagResult::NoChange, ops::FlagResult::Reset,
    ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b10000010U, l->getByte());

  *l = uint8_t { 91U };

  res = ops::decimalAdjust(*l);

  expected = ops::OpResult { ops::FlagResult::Reset, ops::FlagResult::NoChange, ops::FlagResult::Reset,
    ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b10010001U, l->getByte());
}
