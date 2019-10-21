#include "gtest/gtest.h"

#include "cpu/cpuflags.h"


using namespace std;

TEST(CpuFlagsTest, testCarry) {
  uint8_t buf;
  CpuFlags flags(buf);
  flags.setCarry();
  ASSERT_EQ(true, flags.carry());
  flags.clearCarry();
  ASSERT_EQ(false, flags.carry());
}


