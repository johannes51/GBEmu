#include "gtest/gtest.h"

#include "cpu/cpuregisters.h"
#include "util/location.h"


using namespace std;

TEST(CpuRegistersTest, testInitialPc) {
  auto regs = CpuRegisters();
  ASSERT_EQ(0x0100, *regs.pc());
}

TEST(CpuRegistersTest, testInitialAF) {
  auto regs = CpuRegisters();
  ASSERT_EQ(0x01B0, *regs.af());
}

TEST(CpuRegistersTest, testInitialBC) {
  auto regs = CpuRegisters();
  ASSERT_EQ(0x0013, *regs.bc());
}

TEST(CpuRegistersTest, testInitialDE) {
  auto regs = CpuRegisters();
  ASSERT_EQ(0x00D8, *regs.de());
}

TEST(CpuRegistersTest, testInitialHL) {
  auto regs = CpuRegisters();
  ASSERT_EQ(0x014D, *regs.hl());
}


TEST(CpuRegistersTest, testInitialSp) {
  auto regs = CpuRegisters();
  ASSERT_EQ(0xFFFF, *regs.sp());
}


