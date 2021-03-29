#include "gtest/gtest.h"

#include "cpu/cpuregisters.h"
#include "location/location.h"

TEST(CpuRegistersTest, testInitialPc)
{
  CpuRegisters regs;
  EXPECT_EQ(0x0100, regs.get(WordRegisters::PC).get());
}

TEST(CpuRegistersTest, testWritePc)
{
  CpuRegisters regs;
  EXPECT_EQ(0x0100, regs.get(WordRegisters::PC).get());
  regs.get(WordRegisters::PC).set(0x3A4C);
  EXPECT_EQ(0x3A4C, regs.get(WordRegisters::PC).get());
}

TEST(CpuRegistersTest, testInitialAF)
{
  CpuRegisters regs;
  EXPECT_EQ(0x01B0, regs.get(WordRegisters::AF).get());
}

TEST(CpuRegistersTest, testInitialBC)
{
  CpuRegisters regs;
  EXPECT_EQ(0x0013, regs.get(WordRegisters::BC).get());
}

TEST(CpuRegistersTest, testInitialBCsplit)
{
  CpuRegisters regs;
  EXPECT_EQ(0x0013, regs.get(WordRegisters::BC).get());
  regs.get(WordRegisters::BC).set(0x74F1);
  EXPECT_EQ(0x74, regs.get(ByteRegisters::B).get());
  EXPECT_EQ(0xF1, regs.get(ByteRegisters::C).get());
}

TEST(CpuRegistersTest, testInitialDE)
{
  CpuRegisters regs;
  EXPECT_EQ(0x00D8, regs.get(WordRegisters::DE).get());
}

TEST(CpuRegistersTest, testInitialDEsplit)
{
  CpuRegisters regs;
  EXPECT_EQ(0x00D8, regs.get(WordRegisters::DE).get());
  regs.get(ByteRegisters::D).set(0x82);
  regs.get(ByteRegisters::E).set(0xB5);
  EXPECT_EQ(0x82B5, regs.get(WordRegisters::DE).get());
}

TEST(CpuRegistersTest, testInitialHL)
{
  CpuRegisters regs;
  EXPECT_EQ(0x014D, regs.get(WordRegisters::HL).get());
}

TEST(CpuRegistersTest, testInitialH)
{
  CpuRegisters regs;
  EXPECT_EQ(0x01, regs.get(ByteRegisters::H).get());
}

TEST(CpuRegistersTest, testInitialL)
{
  CpuRegisters regs;
  EXPECT_EQ(0x4D, regs.get(ByteRegisters::L).get());
}

TEST(CpuRegistersTest, testInitialSp)
{
  CpuRegisters regs;
  EXPECT_EQ(0xFFFF, regs.get(WordRegisters::SP).get());
}

TEST(CpuRegistersTest, testNonByte)
{
  CpuRegisters regs;
  EXPECT_ANY_THROW(regs.get(ByteRegisters::None));
}

TEST(CpuRegistersTest, testNoneWord)
{
  CpuRegisters regs;
  EXPECT_ANY_THROW(regs.get(WordRegisters::None));
}
