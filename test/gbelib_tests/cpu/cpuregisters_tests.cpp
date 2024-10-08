#include "gtest/gtest.h"

#include "cpu/cpuregisters.h"

TEST(CpuRegistersTest, InitialPc)
{
  CpuRegisters regs;
  EXPECT_EQ(0x0100, regs.get(WordRegister::PC)->getWord());
}

TEST(CpuRegistersTest, WritePc)
{
  CpuRegisters regs;
  EXPECT_EQ(0x0100, regs.get(WordRegister::PC)->getWord());
  *regs.get(WordRegister::PC) = uint16_t(0x3A4C);
  EXPECT_EQ(0x3A4C, regs.get(WordRegister::PC)->getWord());
}

TEST(CpuRegistersTest, InitialAF)
{
  CpuRegisters regs;
  EXPECT_EQ(0x01B0, regs.get(WordRegister::AF)->getWord());
}

TEST(CpuRegistersTest, InitialBC)
{
  CpuRegisters regs;
  EXPECT_EQ(0x0013, regs.get(WordRegister::BC)->getWord());
}

TEST(CpuRegistersTest, InitialBCsplit)
{
  CpuRegisters regs;
  EXPECT_EQ(0x0013, regs.get(WordRegister::BC)->getWord());
  *regs.get(WordRegister::BC) = uint16_t(0x74F1);
  EXPECT_EQ(0x74, regs.get(ByteRegister::B)->getByte());
  EXPECT_EQ(0xF1, regs.get(ByteRegister::C)->getByte());
}

TEST(CpuRegistersTest, InitialDE)
{
  CpuRegisters regs;
  EXPECT_EQ(0x00D8, regs.get(WordRegister::DE)->getWord());
}

TEST(CpuRegistersTest, InitialDEsplit)
{
  CpuRegisters regs;
  EXPECT_EQ(0x00D8, regs.get(WordRegister::DE)->getWord());
  *regs.get(ByteRegister::D) = uint8_t(0x82);
  *regs.get(ByteRegister::E) = uint8_t(0xB5);
  EXPECT_EQ(0x82B5, regs.get(WordRegister::DE)->getWord());
}

TEST(CpuRegistersTest, InitialHL)
{
  CpuRegisters regs;
  EXPECT_EQ(0x014D, regs.get(WordRegister::HL)->getWord());
}

TEST(CpuRegistersTest, InitialH)
{
  CpuRegisters regs;
  EXPECT_EQ(0x01, regs.get(ByteRegister::H)->getByte());
}

TEST(CpuRegistersTest, InitialL)
{
  CpuRegisters regs;
  EXPECT_EQ(0x4D, regs.get(ByteRegister::L)->getByte());
}

TEST(CpuRegistersTest, InitialSp)
{
  CpuRegisters regs;
  EXPECT_EQ(0xFFFF, regs.get(WordRegister::SP)->getWord());
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
