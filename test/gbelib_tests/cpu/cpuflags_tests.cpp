#include "gtest/gtest.h"

#include "cpu/cpuflags.h"

TEST(CpuFlagsTest, Zero)
{
  uint8_t buf = 0;
  CpuFlags flags(buf);
  EXPECT_EQ(false, flags.zero());
  flags.setZero();
  EXPECT_EQ(true, flags.zero());
  flags.clearZero();
  EXPECT_EQ(false, flags.zero());
}

TEST(CpuFlagsTest, Carry)
{
  uint8_t buf = 0;
  CpuFlags flags(buf);
  EXPECT_EQ(false, flags.carry());
  flags.setCarry();
  EXPECT_EQ(true, flags.carry());
  flags.clearCarry();
  EXPECT_EQ(false, flags.carry());
}

TEST(CpuFlagsTest, Interrupt)
{
  uint8_t buf = 0;
  CpuFlags flags(buf);
  EXPECT_EQ(true, flags.interruptEnabled());
  flags.disableInterrupt();
  EXPECT_EQ(false, flags.interruptEnabled());
  flags.enableInterrupt();
  EXPECT_EQ(true, flags.interruptEnabled());
}
