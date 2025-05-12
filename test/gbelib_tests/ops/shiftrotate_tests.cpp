#include "gtest/gtest.h"

#include "ops/shiftrotate.h"

#include "location/variablelocation.h"

TEST(ShiftrotateTest, RLC)
{
  auto l = variableLocation(uint8_t { 0b01100000U });

  auto res = ops::rl(*l);

  auto expected = ops::OpResult { ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Reset,
    ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b11000000U, l->get());

  res = ops::rl(*l);

  expected
      = ops::OpResult { ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Set };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b10000001U, l->get());

  res = ops::rl(*l);

  expected
      = ops::OpResult { ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Set };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b00000011, l->get());

  *l = uint8_t { 0b00000000U };
  res = ops::rl(*l);

  expected
      = ops::OpResult { ops::FlagResult::Set, ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
}

TEST(ShiftrotateTest, RL)
{
  auto l = variableLocation(uint8_t { 0b01100000U });

  auto res = ops::rl(*l, true);

  auto expected = ops::OpResult { ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Reset,
    ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b11000001U, l->get());

  res = ops::rl(*l, false);

  expected
      = ops::OpResult { ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Set };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b10000010U, l->get());

  *l = uint8_t { 0b00000000U };
  res = ops::rl(*l, false);

  expected
      = ops::OpResult { ops::FlagResult::Set, ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
}

TEST(ShiftrotateTest, RRC)
{
  auto l = variableLocation(uint8_t { 0b00000110U });

  auto res = ops::rr(*l);

  auto expected = ops::OpResult { ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Reset,
    ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b00000011U, l->get());

  res = ops::rr(*l);

  expected
      = ops::OpResult { ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Set };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b10000001U, l->get());

  res = ops::rr(*l);

  expected
      = ops::OpResult { ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Set };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b11000000U, l->get());

  *l = uint8_t { 0b00000000U };
  res = ops::rr(*l);

  expected
      = ops::OpResult { ops::FlagResult::Set, ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
}

TEST(ShiftrotateTest, RR)
{
  auto l = variableLocation(uint8_t { 0b00000110U });

  auto res = ops::rr(*l, true);

  auto expected = ops::OpResult { ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Reset,
    ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b10000011U, l->get());

  res = ops::rr(*l, false);

  expected
      = ops::OpResult { ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Set };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b01000001U, l->get());

  *l = uint8_t { 0b00000000U };
  res = ops::rr(*l, false);

  expected
      = ops::OpResult { ops::FlagResult::Set, ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
}

TEST(ShiftrotateTest, SLA)
{
  auto l = variableLocation(uint8_t { 0b01100000U });

  auto res = ops::sla(*l);

  auto expected = ops::OpResult { ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Reset,
    ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b11000000U, l->get());

  res = ops::sla(*l);

  expected
      = ops::OpResult { ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Set };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b10000000U, l->get());

  res = ops::sla(*l);

  expected
      = ops::OpResult { ops::FlagResult::Set, ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Set };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b00000000, l->get());
}

TEST(ShiftrotateTest, SRA)
{
  auto l = variableLocation(uint8_t { 0b10000110U });

  auto res = ops::sra(*l);

  auto expected = ops::OpResult { ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Reset,
    ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b11000011U, l->get());

  res = ops::sra(*l);

  expected
      = ops::OpResult { ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Set };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b11100001U, l->get());

  *l = uint8_t { 0b00000001U };

  res = ops::sra(*l);

  expected
      = ops::OpResult { ops::FlagResult::Set, ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Set };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b00000000, l->get());
}

TEST(ShiftrotateTest, SRL)
{
  auto l = variableLocation(uint8_t { 0b10000110U });

  auto res = ops::srl(*l);

  auto expected = ops::OpResult { ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Reset,
    ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b01000011U, l->get());

  res = ops::srl(*l);

  expected
      = ops::OpResult { ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Set };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b00100001U, l->get());

  *l = uint8_t { 0b00000001U };

  res = ops::srl(*l);

  expected
      = ops::OpResult { ops::FlagResult::Set, ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Set };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b00000000, l->get());
}

TEST(ShiftrotateTest, SWAP)
{
  auto l = variableLocation(uint8_t { 0b10000110U });

  auto res = ops::swap(*l);

  auto expected = ops::OpResult { ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Reset,
    ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b01101000U, l->get());

  *l = uint8_t { 0b00000001U };

  res = ops::swap(*l);

  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b00010000U, l->get());

  *l = uint8_t { 0b00000000U };

  res = ops::srl(*l);

  expected
      = ops::OpResult { ops::FlagResult::Set, ops::FlagResult::Reset, ops::FlagResult::Reset, ops::FlagResult::Reset };
  EXPECT_EQ(expected, res);
  EXPECT_EQ(0b00000000, l->get());
}
