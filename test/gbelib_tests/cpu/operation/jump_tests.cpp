#include "gtest/gtest.h"

#include "cpu/cpuregisters.h"
#include "cpu/operation/jump.h"
#include "location/location.h"

#include "debug/variablebyte.h"

TEST(JumpTest, testDirect)
{
  Jump jump { JumpType::Direct };
  EXPECT_FALSE(jump.isComplete());
  EXPECT_NO_THROW(jump.nextOpcode(Location<uint8_t>::generate(std::make_unique<VariableByte>(0x5E))));
  EXPECT_FALSE(jump.isComplete());
  EXPECT_NO_THROW(jump.nextOpcode(Location<uint8_t>::generate(std::make_unique<VariableByte>(0x19))));
  ASSERT_TRUE(jump.isComplete());

  EXPECT_FALSE(jump.isDone());
  EXPECT_NO_THROW(jump.clock());
  EXPECT_FALSE(jump.isDone());
  EXPECT_NO_THROW(jump.clock());
  EXPECT_FALSE(jump.isDone());
  EXPECT_NO_THROW(jump.clock());
  EXPECT_FALSE(jump.isDone());
  EXPECT_NO_THROW(jump.clock());
  ASSERT_TRUE(jump.isDone());

  CpuRegisters r;
  ASSERT_NE(0x195E, r.get(WordRegisters::PC).get());
  jump.execute(r);
  EXPECT_EQ(0x195E, r.get(WordRegisters::PC).get());
}
