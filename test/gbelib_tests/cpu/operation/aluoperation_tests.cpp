#include "gtest/gtest.h"

#include "cpu/cpuregisters.h"
#include "cpu/operation/aluoperation.h"
#include "location/location.h"
#include "mem/rambank.h"

#include "mock/variablebyte.h"

TEST(AluOperationTest, Xor)
{
  AluOperation xorOp { AluFunction::Xor, Source::Register };
  xorOp.setRegister(ByteRegisters::B);
  ASSERT_TRUE(xorOp.isComplete());

  EXPECT_EQ(1, xorOp.cycles());

  CpuRegisters r;
  auto a = r.get(ByteRegisters::A);
  a.set(0x9); // 1001
  ASSERT_EQ(0x9, a.get());
  auto b = r.get(ByteRegisters::B);
  b.set(0x5); // 0101
  ASSERT_EQ(0x5, b.get());

  IMemoryViewSP m;
  xorOp.execute(r, *m);
  EXPECT_EQ(0xC, r.get(ByteRegisters::A).get()); // 1100
}

TEST(AluOperationTest, AddImmediate)
{
  AluOperation addOp { AluFunction::Add, Source::Immediate };
  ASSERT_FALSE(addOp.isComplete());
  ASSERT_NO_THROW(addOp.nextOpcode(Location<uint8_t>::generate(std::make_unique<VariableByte>(0x4D))));
  ASSERT_TRUE(addOp.isComplete());
  ASSERT_ANY_THROW(addOp.nextOpcode(Location<uint8_t>::generate(std::make_unique<VariableByte>(0x4D))));

  EXPECT_EQ(2, addOp.cycles());

  CpuRegisters r;
  r.get(ByteRegisters::A).set(0x05);

  IMemoryViewSP m;
  addOp.execute(r, *m);
  EXPECT_EQ(0x52, r.get(ByteRegisters::A).get());
}

TEST(AluOperationTest, Dec)
{
  AluOperation decOp { AluFunction::Dec, Source::None };
  decOp.setRegister(ByteRegisters::B);
  ASSERT_TRUE(decOp.isComplete());

  EXPECT_EQ(1, decOp.cycles());

  CpuRegisters r;
  auto b = r.get(ByteRegisters::B);
  b.set(0x5); // 0101
  ASSERT_EQ(0x5, b.get());

  IMemoryViewSP m;
  decOp.execute(r, *m);
  EXPECT_EQ(0x4, r.get(ByteRegisters::B).get()); // 0100
}

TEST(AluOperationTest, DecIndirect)
{
  AluOperation decOp { AluFunction::Dec, Source::Indirect };
  ASSERT_TRUE(decOp.isComplete());

  EXPECT_EQ(3, decOp.cycles());

  CpuRegisters r;
  r.get(WordRegisters::HL).set(0x0100);

  RamBank m { { 0x0100, 0x0101 } };
  m.getByte(0x0100).set(0x13);
  decOp.execute(r, m);
  EXPECT_EQ(0x12, m.getByte(0x0100).get());
}

TEST(AluOperationTest, Throws)
{
  CpuRegisters r;
  IMemoryViewSP m;

  AluOperation decOp { AluFunction::Add, Source::Register };
  EXPECT_ANY_THROW(decOp.execute(r, *m));

  AluOperation decOp2 { AluFunction::Add, Source::None };
  EXPECT_ANY_THROW(decOp2.execute(r, *m));
}
