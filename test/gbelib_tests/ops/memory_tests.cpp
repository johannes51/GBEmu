#include "gtest/gtest.h"

#include "location/location.h"
#include "location/rambyte.h"
#include "ops/memory.h"

#include "location/variablebyte.h"

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
