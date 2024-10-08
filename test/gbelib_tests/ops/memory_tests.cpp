#include "gtest/gtest.h"

#include "location/location.h"
#include "ops/memory.h"

#include "location/variablelocation.h"

TEST(OpsTest, Load8)
{
  auto d = variableLocation(uint8_t(0x3C));
  auto s = variableLocation(uint8_t(0xF1));

  ops::load<uint8_t>(*d, *s);

  EXPECT_EQ(0xF1, d->getByte());
}

TEST(OpsTest, Load16)
{
  auto d = variableLocation(0x3C, 0xB8);
  auto s = variableLocation(0xF1, 0xC3);

  ops::load<uint16_t>(*d, *s);

  EXPECT_EQ(0xC3F1, d->getWord());
}
