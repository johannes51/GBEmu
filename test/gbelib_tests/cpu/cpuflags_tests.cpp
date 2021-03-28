#include "gtest/gtest.h"

#include "cpu/cpuflags.h"

TEST(CpuFlagsTest, testCarry)
{
  uint8_t buf = 0;
  CpuFlags flags_anon(buf);
  FlagsView& flags = flags_anon;
  EXPECT_EQ(false, flags.carry());
  flags.setCarry();
  EXPECT_EQ(true, flags.carry());
  flags.clearCarry();
  EXPECT_EQ(false, flags.carry());
}

TEST(CpuFlagsTest, testInterrupt)
{
  uint8_t buf = 0;
  CpuFlags flags_anon(buf);
  FlagsView& flags = flags_anon;
  EXPECT_EQ(true, flags.interruptEnabled());
  flags.disableInterrupt();
  EXPECT_EQ(false, flags.interruptEnabled());
  flags.enableInterrupt();
  EXPECT_EQ(true, flags.interruptEnabled());
}
