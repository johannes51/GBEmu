#include "gtest/gtest.h"

#include "cpu/cpuregisters.h"
#include "cpu/operation/jump.h"
#include "location/location.h"

#include "mock/variablebyte.h"

TEST(JumpTest, Direct)
{
  Jump jump { JumpType::Direct };
  EXPECT_FALSE(jump.isComplete());
  EXPECT_NO_THROW(jump.nextOpcode(variableLocation(0x5E)));
  EXPECT_FALSE(jump.isComplete());
  EXPECT_NO_THROW(jump.nextOpcode(variableLocation(0x19)));
  ASSERT_TRUE(jump.isComplete());

  EXPECT_EQ(4, jump.cycles());

  CpuRegisters r;
  ASSERT_NE(0x195E, r.get(WordRegisters::PC).get());
  jump.execute(r, *IMemoryViewSP());
  EXPECT_EQ(0x195E, r.get(WordRegisters::PC).get());
}

TEST(JumpTest, Relative)
{
  Jump jump { JumpType::Relative };
  EXPECT_FALSE(jump.isComplete());
  EXPECT_NO_THROW(jump.nextOpcode(variableLocation(0x1A)));
  ASSERT_TRUE(jump.isComplete());

  EXPECT_EQ(4, jump.cycles());

  CpuRegisters r;
  r.get(WordRegisters::PC).set(0x1900);
  jump.execute(r, *IMemoryViewSP());
  EXPECT_EQ(0x191A, r.get(WordRegisters::PC).get());
}

TEST(JumpTest, Next)
{
  Jump jump { JumpType::Direct };
  EXPECT_FALSE(jump.isComplete());
  EXPECT_NO_THROW(jump.nextOpcode(variableLocation(0x5E)));
  EXPECT_FALSE(jump.isComplete());
  EXPECT_NO_THROW(jump.nextOpcode(variableLocation(0x19)));
  ASSERT_TRUE(jump.isComplete());
  EXPECT_THROW(jump.nextOpcode(variableLocation(0x19)), std::logic_error);
}
