#include "gtest/gtest.h"

#include "cpu/cpuflags.h"

TEST(CpuFlagsTest, testCarry) {
  uint8_t buf;
  CpuFlags flags(buf);
  flags.setCarry();
  EXPECT_EQ(true, flags.carry());
  flags.clearCarry();
  EXPECT_EQ(false, flags.carry());
}
