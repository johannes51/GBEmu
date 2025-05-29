#include "gtest/gtest.h"

#include "cpu/registers/cpuregisters.h"

TEST(CpuRegistersTest, InitialPc)
{
  CpuRegisters regs;
  EXPECT_EQ(0x0100, regs.get(WordRegister::PC).get());
}

TEST(CpuRegistersTest, WritePc)
{
  CpuRegisters regs;
  EXPECT_EQ(0x0100, regs.get(WordRegister::PC).get());
  regs.get(WordRegister::PC) = uint16_t { 0x3A4C };
  EXPECT_EQ(0x3A4C, regs.get(WordRegister::PC).get());
}

TEST(CpuRegistersTest, InitialAF)
{
  CpuRegisters regs;
  EXPECT_EQ(0x01B0, regs.get(WordRegister::AF).get());
}

TEST(CpuRegistersTest, InitialBC)
{
  CpuRegisters regs;
  EXPECT_EQ(0x0013, regs.get(WordRegister::BC).get());
}

TEST(CpuRegistersTest, InitialBCsplit)
{
  CpuRegisters regs;
  EXPECT_EQ(0x0013, regs.get(WordRegister::BC).get());
  regs.get(WordRegister::BC) = uint16_t { 0x74F1 };
  EXPECT_EQ(0x74, regs.get(ByteRegister::B).get());
  EXPECT_EQ(0xF1, regs.get(ByteRegister::C).get());
}

TEST(CpuRegistersTest, InitialDE)
{
  CpuRegisters regs;
  EXPECT_EQ(0x00D8, regs.get(WordRegister::DE).get());
}

TEST(CpuRegistersTest, InitialDEsplit)
{
  CpuRegisters regs;
  EXPECT_EQ(0x00D8, regs.get(WordRegister::DE).get());
  regs.get(ByteRegister::D) = uint8_t { 0x82 };
  regs.get(ByteRegister::E) = uint8_t { 0xB5 };
  EXPECT_EQ(0x82B5, regs.get(WordRegister::DE).get());
}

TEST(CpuRegistersTest, InitialHL)
{
  CpuRegisters regs;
  EXPECT_EQ(0x014D, regs.get(WordRegister::HL).get());
}

TEST(CpuRegistersTest, InitialH)
{
  CpuRegisters regs;
  EXPECT_EQ(0x01, regs.get(ByteRegister::H).get());
}

TEST(CpuRegistersTest, InitialL)
{
  CpuRegisters regs;
  EXPECT_EQ(0x4D, regs.get(ByteRegister::L).get());
}

TEST(CpuRegistersTest, InitialSp)
{
  CpuRegisters regs;
  EXPECT_EQ(0xFFFE, regs.get(WordRegister::SP).get());
}

TEST(CpuRegistersTest, NonByte)
{
  CpuRegisters regs;
  EXPECT_ANY_THROW(regs.get(ByteRegister::None));
}

TEST(CpuRegistersTest, NoneWord)
{
  CpuRegisters regs;
  EXPECT_ANY_THROW(regs.get(WordRegister::None));
}

TEST(CpuRegistersTest, Flags)
{
  CpuRegisters regs;
  EXPECT_NO_THROW(regs.getFlags());
  EXPECT_NO_THROW(const_cast<const CpuRegisters&>(regs).getFlags());
}
