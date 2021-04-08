#include "gtest/gtest.h"

#include "cpu/cpuregisters.h"
#include "cpu/operation/bytealuoperation.h"
#include "location/location.h"
#include "mem/rambank.h"

#include "location/variablebyte.h"

TEST(ByteAluOperationTest, Xor)
{
  ByteAluOperation xorOp { AluFunction::Xor, Source::Register };
  xorOp.setRegister(ByteRegister::B);
  ASSERT_TRUE(xorOp.isComplete());

  CpuRegisters r;
  EXPECT_EQ(1, xorOp.cycles(r));

  auto a = r.get(ByteRegister::A);
  a.set(0x9); // 1001
  ASSERT_EQ(0x9, a.get());
  auto b = r.get(ByteRegister::B);
  b.set(0x5); // 0101
  ASSERT_EQ(0x5, b.get());

  IMemoryViewSP m;
  xorOp.execute(r, *m);
  EXPECT_EQ(0xC, r.get(ByteRegister::A).get()); // 1100
}

TEST(ByteAluOperationTest, AddImmediate)
{
  ByteAluOperation addOp { AluFunction::Add, Source::Immediate };
  ASSERT_FALSE(addOp.isComplete());
  ASSERT_NO_THROW(addOp.nextOpcode(variableLocation(0x4D)));
  ASSERT_TRUE(addOp.isComplete());
  ASSERT_ANY_THROW(addOp.nextOpcode(variableLocation(0x4D)));

  CpuRegisters r;
  EXPECT_EQ(2, addOp.cycles(r));

  r.get(ByteRegister::A).set(0x05);

  IMemoryViewSP m;
  addOp.execute(r, *m);
  EXPECT_EQ(0x52, r.get(ByteRegister::A).get());
}

TEST(ByteAluOperationTest, Inc)
{
  ByteAluOperation decOp { AluFunction::Inc, Source::None };
  decOp.setRegister(ByteRegister::B);
  ASSERT_TRUE(decOp.isComplete());

  CpuRegisters r;
  EXPECT_EQ(1, decOp.cycles(r));

  auto b = r.get(ByteRegister::B);
  b.set(0x1); // 0001
  ASSERT_EQ(0x1, b.get());

  IMemoryViewSP m;
  decOp.execute(r, *m);
  EXPECT_EQ(0x2, r.get(ByteRegister::B).get()); // 0010
}

TEST(ByteAluOperationTest, IncIndirect)
{
  ByteAluOperation decOp { AluFunction::Inc, Source::Indirect };
  ASSERT_TRUE(decOp.isComplete());

  CpuRegisters r;
  EXPECT_EQ(3, decOp.cycles(r));

  r.get(WordRegister::HL).set(0x0100);

  RamBank m { { 0x0100, 0x0101 } };
  m.getByte(0x0100).set(0x13);
  decOp.execute(r, m);
  EXPECT_EQ(0x14, m.getByte(0x0100).get());
}

TEST(ByteAluOperationTest, Dec)
{
  ByteAluOperation decOp { AluFunction::Dec, Source::None };
  decOp.setRegister(ByteRegister::B);
  ASSERT_TRUE(decOp.isComplete());

  CpuRegisters r;
  EXPECT_EQ(1, decOp.cycles(r));

  auto b = r.get(ByteRegister::B);
  b.set(0x1); // 0001
  ASSERT_EQ(0x1, b.get());

  IMemoryViewSP m;
  decOp.execute(r, *m);
  EXPECT_EQ(0x0, r.get(ByteRegister::B).get()); // 0000
}

TEST(ByteAluOperationTest, DecIndirect)
{
  ByteAluOperation decOp { AluFunction::Dec, Source::Indirect };
  ASSERT_TRUE(decOp.isComplete());

  CpuRegisters r;
  EXPECT_EQ(3, decOp.cycles(r));

  r.get(WordRegister::HL).set(0x0100);

  RamBank m { { 0x0100, 0x0101 } };
  m.getByte(0x0100).set(0x13);
  decOp.execute(r, m);
  EXPECT_EQ(0x12, m.getByte(0x0100).get());
}

TEST(ByteAluOperationTest, Throws)
{
  CpuRegisters r;
  IMemoryViewSP m;

  ByteAluOperation decOp { AluFunction::Add, Source::Register };
  EXPECT_ANY_THROW(decOp.execute(r, *m));

  ByteAluOperation decOp2 { AluFunction::Add, Source::None };
  EXPECT_ANY_THROW(decOp2.execute(r, *m));
}
