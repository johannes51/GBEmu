#include "gtest/gtest.h"

#include "location/location.h"
#include "location/rambyte.h"
#include "ops/logic.h"

#include "location/variablebyte.h"

TEST(LogicTest, Xor)
{
  auto d = variableLocation(0x3C);
  auto s = variableLocation(0xF1);

  ops::xorF(d, s);

  EXPECT_EQ(0xCD, d.get());
}

TEST(LogicTest, XorZ)
{
  auto d = variableLocation(0x3C);

  EXPECT_EQ(1, ops::xorF(d, d).z);
}
