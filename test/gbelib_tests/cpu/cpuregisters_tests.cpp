#include "gtest/gtest.h"

#include "cpu/cpuregisters.h"
#include "location/location.h"


using namespace std;

TEST(CpuRegistersTest, testInitialPc) {
  CpuRegisters regs;
  ASSERT_EQ(0x0100, **regs.pc());
}

TEST(CpuRegistersTest, testWritePc) {
  CpuRegisters regs;
  ASSERT_EQ(0x0100, **regs.pc());
  *regs.pc() << 0x3A4C;
  ASSERT_EQ(0x3A4C, **regs.pc());
}

TEST(CpuRegistersTest, testInitialAF) {
  CpuRegisters regs;
  ASSERT_EQ(0x01B0, **regs.af());
}

TEST(CpuRegistersTest, testInitialBC) {
  CpuRegisters regs;
  ASSERT_EQ(0x0013, **regs.bc());
}

TEST(CpuRegistersTest, testInitialBCsplit) {
  CpuRegisters regs;
  ASSERT_EQ(0x0013, **regs.bc());
  *regs.bc() << 0x74F1;
  ASSERT_EQ(0x74, **regs.b());
  ASSERT_EQ(0xF1, **regs.c());
}

TEST(CpuRegistersTest, testInitialDE) {
  CpuRegisters regs;
  ASSERT_EQ(0x00D8, **regs.de());
}

TEST(CpuRegistersTest, testInitialDEsplit) {
  CpuRegisters regs;
  ASSERT_EQ(0x00D8, **regs.de());
  *regs.d() << 0x82;
  *regs.e() << 0xB5;
  ASSERT_EQ(0x82B5, **regs.de());
}

TEST(CpuRegistersTest, testInitialHL) {
  CpuRegisters regs;
  ASSERT_EQ(0x014D, **regs.hl());
}

TEST(CpuRegistersTest, testInitialSp) {
  CpuRegisters regs;
  ASSERT_EQ(0xFFFF, **regs.sp());
}


