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

  EXPECT_EQ(4, jump.cycles());

  CpuRegisters r;
  ASSERT_NE(0x195E, r.get(WordRegisters::PC).get());
  jump.execute(r, *IMemoryViewSP());
  EXPECT_EQ(0x195E, r.get(WordRegisters::PC).get());
}

TEST(JumpTest, testRelative)
{
  Jump jump { JumpType::Relative };
  EXPECT_FALSE(jump.isComplete());
  EXPECT_NO_THROW(jump.nextOpcode(Location<uint8_t>::generate(std::make_unique<VariableByte>(0x1A))));
  ASSERT_TRUE(jump.isComplete());

  EXPECT_EQ(4, jump.cycles());

  CpuRegisters r;
  r.get(WordRegisters::PC).set(0x1900);
  jump.execute(r, *IMemoryViewSP());
  EXPECT_EQ(0x191A, r.get(WordRegisters::PC).get());
}

TEST(JumpTest, testNext)
{
  Jump jump { JumpType::Direct };
  EXPECT_FALSE(jump.isComplete());
  EXPECT_NO_THROW(jump.nextOpcode(Location<uint8_t>::generate(std::make_unique<VariableByte>(0x5E))));
  EXPECT_FALSE(jump.isComplete());
  EXPECT_NO_THROW(jump.nextOpcode(Location<uint8_t>::generate(std::make_unique<VariableByte>(0x19))));
  ASSERT_TRUE(jump.isComplete());
  EXPECT_THROW(jump.nextOpcode(Location<uint8_t>::generate(std::make_unique<VariableByte>(0x19))), std::logic_error);
}
