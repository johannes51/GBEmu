#include "gtest/gtest.h"

#include "cpu/cpuflags.h"

TEST(CpuFlagsTest, testCarry)
{
  uint8_t buf = 0;
  CpuFlags flags_anon(buf);
  FlagsView& flags = flags_anon;
  flags.setCarry();
  EXPECT_EQ(true, flags.carry());
  flags.clearCarry();
  EXPECT_EQ(false, flags.carry());
}
