#include "gtest/gtest.h"

#include "location/location.h"
#include "location/rambyte.h"
#include "ops/arithmetic.h"

#include "location/variablebyte.h"

TEST(ArithmeticTest, Increment8)
{
  auto l = variableLocation(5);

  ops::increment(l);

  EXPECT_EQ(6, l.get());
}

TEST(ArithmeticTest, Increment8Carry)
{
  auto l = variableLocation(255);

  ops::increment(l);

  EXPECT_EQ(0, l.get());
}

TEST(ArithmeticTest, Increment16)
{
  auto l = variableLocation(0xFF, 0xAF);

  ops::increment(l);

  EXPECT_EQ(0xB000, l.get());
}

TEST(ArithmeticTest, Add8)
{
  auto lA = variableLocation(5);
  auto lB = variableLocation(13);

  ops::add(lA, lB);

  EXPECT_EQ(5 + 13, lA.get());
}

TEST(ArithmeticTest, Add8Z)
{
  auto lA = variableLocation(0);
  auto lB = variableLocation(0);

  EXPECT_EQ(1, ops::add(lA, lB).z);
}

TEST(ArithmeticTest, Add16)
{
  auto lA = variableLocation(0x35, 0x14);
  auto lB = variableLocation(0xA2, 0xC7);

  ops::add(lA, lB);

  EXPECT_EQ(0xDBD7, lA.get());
}

TEST(ArithmeticTest, Add16Z)
{
  auto lA = variableLocation(0x0, 0x0);
  auto lB = variableLocation(0x0, 0x0);

  EXPECT_EQ(1, ops::add(lA, lB).z);
}
