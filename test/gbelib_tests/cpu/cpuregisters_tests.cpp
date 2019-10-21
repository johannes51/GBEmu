#include "gtest/gtest.h"

#include "cpu/cpuregisters.h"
#include "location/location.h"


using namespace std;

TEST(CpuRegistersTest, testInitialPc) {
  CpuRegisters regs;
  ASSERT_EQ(0x0100, regs.pc()->get());
}

TEST(CpuRegistersTest, testWritePc) {
  CpuRegisters regs;
  ASSERT_EQ(0x0100, regs.pc()->get());
  regs.pc()->set(0x3A4C);
  ASSERT_EQ(0x3A4C, regs.pc()->get());
}

TEST(CpuRegistersTest, testInitialAF) {
  CpuRegisters regs;
  ASSERT_EQ(0x01B0, regs.af()->get());
}

TEST(CpuRegistersTest, testInitialBC) {
  CpuRegisters regs;
  ASSERT_EQ(0x0013, regs.bc()->get());
}

TEST(CpuRegistersTest, testInitialBCsplit) {
  CpuRegisters regs;
  ASSERT_EQ(0x0013, regs.bc()->get());
  regs.bc()->set(0x74F1);
  ASSERT_EQ(0x74, regs.b()->get());
  ASSERT_EQ(0xF1, regs.c()->get());
}

TEST(CpuRegistersTest, testInitialDE) {
  CpuRegisters regs;
  ASSERT_EQ(0x00D8, regs.de()->get());
}

TEST(CpuRegistersTest, testInitialDEsplit) {
  CpuRegisters regs;
  ASSERT_EQ(0x00D8, regs.de()->get());
  regs.d()->set(0x82);
  regs.e()->set(0xB5);
  ASSERT_EQ(0x82B5, regs.de()->get());
}

TEST(CpuRegistersTest, testInitialHL) {
  CpuRegisters regs;
  ASSERT_EQ(0x014D, regs.hl()->get());
}

TEST(CpuRegistersTest, testInitialSp) {
  CpuRegisters regs;
  ASSERT_EQ(0xFFFF, regs.sp()->get());
}
