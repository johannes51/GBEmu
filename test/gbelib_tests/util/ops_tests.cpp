#include "gtest/gtest.h"

#include "location/location.h"
#include "location/rambyte.h"
#include "util/ops.h"

#include "mock/variablebyte.h"

TEST(OpsTest, Increment8)
{
  auto l = variableLocation(5);

  ops::increment(l);

  EXPECT_EQ(6, l.get());
}

TEST(OpsTest, Increment8Carry)
{
  auto l = variableLocation(255);

  ops::increment(l);

  EXPECT_EQ(0, l.get());
}

TEST(OpsTest, Increment16)
{
  auto l = variableLocation(0xFF, 0xAF);

  ops::increment(l);

  EXPECT_EQ(0xB000, l.get());
}

TEST(OpsTest, Add8)
{
  auto lA = variableLocation(5);
  auto lB = variableLocation(13);

  ops::add(lA, lB);

  EXPECT_EQ(5 + 13, lA.get());
}

TEST(OpsTest, Add8Z)
{
  auto lA = variableLocation(0);
  auto lB = variableLocation(0);

  EXPECT_EQ(1, ops::add(lA, lB).z);
}

TEST(OpsTest, Add16)
{
  auto lA = variableLocation(0x35, 0x14);
  auto lB = variableLocation(0xA2, 0xC7);

  ops::add(lA, lB);

  EXPECT_EQ(0xDBD7, lA.get());
}

TEST(OpsTest, Add16Z)
{
  auto lA = variableLocation(0x0, 0x0);

  EXPECT_EQ(1, ops::add(lA, 0).z);
}

TEST(OpsTest, Load8)
{
  auto d = variableLocation(0x3C);
  auto s = variableLocation(0xF1);

  ops::load(d, s);

  EXPECT_EQ(0xF1, d.get());
}

TEST(OpsTest, Load16)
{
  auto d = variableLocation(0x3C, 0xB8);
  auto s = variableLocation(0xF1, 0xC3);

  ops::load(d, s);

  EXPECT_EQ(0xC3F1, d.get());
}

TEST(OpsTest, Xor)
{
  auto d = variableLocation(0x3C);
  auto s = variableLocation(0xF1);

  ops::xorF(d, s);

  EXPECT_EQ(0xCD, d.get());
}

TEST(OpsTest, XorZ)
{
  auto d = variableLocation(0x3C);

  EXPECT_EQ(1, ops::xorF(d, d).z);
}
