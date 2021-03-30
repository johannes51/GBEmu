#include "gtest/gtest.h"

#include "cpu/cpuregisters.h"
#include "location/location.h"

TEST(CpuRegistersTest, InitialPc)
{
  CpuRegisters regs;
  EXPECT_EQ(0x0100, regs.get(WordRegisters::PC).get());
}

TEST(CpuRegistersTest, WritePc)
{
  CpuRegisters regs;
  EXPECT_EQ(0x0100, regs.get(WordRegisters::PC).get());
  regs.get(WordRegisters::PC).set(0x3A4C);
  EXPECT_EQ(0x3A4C, regs.get(WordRegisters::PC).get());
}

TEST(CpuRegistersTest, InitialAF)
{
  CpuRegisters regs;
  EXPECT_EQ(0x01B0, regs.get(WordRegisters::AF).get());
}

TEST(CpuRegistersTest, InitialBC)
{
  CpuRegisters regs;
  EXPECT_EQ(0x0013, regs.get(WordRegisters::BC).get());
}

TEST(CpuRegistersTest, InitialBCsplit)
{
  CpuRegisters regs;
  EXPECT_EQ(0x0013, regs.get(WordRegisters::BC).get());
  regs.get(WordRegisters::BC).set(0x74F1);
  EXPECT_EQ(0x74, regs.get(ByteRegisters::B).get());
  EXPECT_EQ(0xF1, regs.get(ByteRegisters::C).get());
}

TEST(CpuRegistersTest, InitialDE)
{
  CpuRegisters regs;
  EXPECT_EQ(0x00D8, regs.get(WordRegisters::DE).get());
}

TEST(CpuRegistersTest, InitialDEsplit)
{
  CpuRegisters regs;
  EXPECT_EQ(0x00D8, regs.get(WordRegisters::DE).get());
  regs.get(ByteRegisters::D).set(0x82);
  regs.get(ByteRegisters::E).set(0xB5);
  EXPECT_EQ(0x82B5, regs.get(WordRegisters::DE).get());
}

TEST(CpuRegistersTest, InitialHL)
{
  CpuRegisters regs;
  EXPECT_EQ(0x014D, regs.get(WordRegisters::HL).get());
}

TEST(CpuRegistersTest, InitialH)
{
  CpuRegisters regs;
  EXPECT_EQ(0x01, regs.get(ByteRegisters::H).get());
}

TEST(CpuRegistersTest, InitialL)
{
  CpuRegisters regs;
  EXPECT_EQ(0x4D, regs.get(ByteRegisters::L).get());
}

TEST(CpuRegistersTest, InitialSp)
{
  CpuRegisters regs;
  EXPECT_EQ(0xFFFF, regs.get(WordRegisters::SP).get());
}

TEST(CpuRegistersTest, NonByte)
{
  CpuRegisters regs;
  EXPECT_ANY_THROW(regs.get(ByteRegisters::None));
}

TEST(CpuRegistersTest, NoneWord)
{
  CpuRegisters regs;
  EXPECT_ANY_THROW(regs.get(WordRegisters::None));
}
