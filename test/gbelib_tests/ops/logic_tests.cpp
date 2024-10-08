#include "gtest/gtest.h"

#include "location/location.h"
#include "ops/logic.h"

#include "location/variablelocation.h"

TEST(LogicTest, Xor)
{
  auto d = variableLocation(uint8_t { 0x3C });
  auto s = variableLocation(uint8_t { 0xF1 });

  ops::xorF(*d, *s);

  EXPECT_EQ(0xCD, d->getByte());
}

TEST(LogicTest, XorZ)
{
  auto d = variableLocation(uint8_t { 0x3C });

  EXPECT_EQ(ops::FlagResult::Set, ops::xorF(*d, *d).z);
}
