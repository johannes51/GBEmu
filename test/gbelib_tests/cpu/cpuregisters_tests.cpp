#include "gtest/gtest.h"

#include "cpu/cpuregisters.h"
#include "util/location.h"


using namespace std;

TEST(CpuRegistersTest, testInitialPc) {
  auto regs = CpuRegisters();
  ASSERT_EQ(0x0100, *regs.pc());
}


