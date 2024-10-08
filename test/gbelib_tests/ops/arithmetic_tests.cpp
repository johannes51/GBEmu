#include "gtest/gtest.h"

#include "location/location.h"
#include "location/ramlocation.h"
#include "ops/arithmetic.h"

#include "location/variablelocation.h"

TEST(ArithmeticTest, Increment8)
{
  auto l = variableLocation(uint8_t { 5 });

  ops::increment<uint8_t>(*l);

  EXPECT_EQ(6, l->getByte());
}

TEST(ArithmeticTest, Increment8Carry)
{
  auto l = variableLocation(uint8_t { 255 });

  ops::increment<uint8_t>(*l);

  EXPECT_EQ(0, l->getByte());
}

TEST(ArithmeticTest, Increment16)
{
  auto l = variableLocation(0xFF, 0xAF);

  ops::increment<uint16_t>(*l);

  EXPECT_EQ(0xB000, l->getWord());
}

TEST(ArithmeticTest, Add8)
{
  auto lA = variableLocation(uint8_t { 5 });
  auto lB = variableLocation(uint8_t { 13 });

  ops::add<uint8_t>(*lA, *lB);

  EXPECT_EQ(5 + 13, lA->getByte());
}

TEST(ArithmeticTest, Add8Z)
{
  auto lA = variableLocation(uint8_t { 0 });
  auto lB = variableLocation(uint8_t { 0 });

  EXPECT_EQ(ops::FlagResult::Set, ops::add<uint8_t>(*lA, *lB).z);
}

TEST(ArithmeticTest, Add16)
{
  auto lA = variableLocation(0x35, 0x14);
  auto lB = variableLocation(0xA2, 0xC7);

  ops::add<uint16_t>(*lA, *lB);

  EXPECT_EQ(0xDBD7, lA->getWord());
}

TEST(ArithmeticTest, Add16Z)
{
  auto lA = variableLocation(0x0, 0x0);
  auto lB = variableLocation(0x0, 0x0);

  EXPECT_EQ(ops::FlagResult::Set, ops::add<uint16_t>(*lA, *lB).z);
}
