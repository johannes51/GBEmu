#include "gtest/gtest.h"

#include "cpu/cpuregisters.h"
#include "cpu/operation/bytealuoperation.h"
#include "location/location.h"
#include "mock/testbank.h"

#include "location/variablelocation.h"

TEST(ByteAluOperationTest, Xor)
{
  ByteAluOperation xorOp { ByteAluFunction::Xor, Source::Register };
  xorOp.setRegister(ByteRegister::B);
  ASSERT_TRUE(xorOp.isComplete());

  CpuRegisters r;
  EXPECT_EQ(1, xorOp.cycles());

  auto a = r.get(ByteRegister::A);
  *a = uint8_t(0x9); // 1001
  ASSERT_EQ(0x9, a->getByte());
  auto b = r.get(ByteRegister::B);
  *b = uint8_t(0x5); // 0101
  ASSERT_EQ(0x5, b->getByte());

  IMemoryViewSP m;
  xorOp.execute(r, *m);
  EXPECT_EQ(0xC, r.get(ByteRegister::A)->getByte()); // 1100
}

TEST(ByteAluOperationTest, AddImmediate)
{
  ByteAluOperation addOp { ByteAluFunction::Add, Source::Immediate };
  ASSERT_FALSE(addOp.isComplete());
  ASSERT_NO_THROW(addOp.nextOpcode(variableLocation(uint8_t(0x4D))));
  ASSERT_TRUE(addOp.isComplete());
  ASSERT_ANY_THROW(addOp.nextOpcode(variableLocation(uint8_t(0x4D))));

  CpuRegisters r;
  EXPECT_EQ(2, addOp.cycles());

  *r.get(ByteRegister::A) = uint8_t(0x05);

  IMemoryViewSP m;
  addOp.execute(r, *m);
  EXPECT_EQ(0x52, r.get(ByteRegister::A)->getByte());
}

TEST(ByteAluOperationTest, Inc)
{
  ByteAluOperation decOp { ByteAluFunction::Inc, Source::Register };
  decOp.setRegister(ByteRegister::B);
  ASSERT_TRUE(decOp.isComplete());

  CpuRegisters r;
  EXPECT_EQ(1, decOp.cycles());

  auto b = r.get(ByteRegister::B);
  *b = uint8_t(0x1); // 0001
  ASSERT_EQ(0x1, b->getByte());

  IMemoryViewSP m;
  decOp.execute(r, *m);
  EXPECT_EQ(0x2, r.get(ByteRegister::B)->getByte()); // 0010
}

TEST(ByteAluOperationTest, IncIndirect)
{
  ByteAluOperation decOp { ByteAluFunction::Inc, Source::Indirect };
  ASSERT_TRUE(decOp.isComplete());

  CpuRegisters r;
  EXPECT_EQ(3, decOp.cycles());

  *r.get(WordRegister::HL) = uint16_t(0x0100);

  TestBank m { { 0x0100, 0x0101 } };
  *m.getLocation(0x0100) = uint8_t(0x13);
  decOp.execute(r, m);
  EXPECT_EQ(0x14, m.getLocation(0x0100)->getByte());
}

TEST(ByteAluOperationTest, Dec)
{
  ByteAluOperation decOp { ByteAluFunction::Dec, Source::Register };
  decOp.setRegister(ByteRegister::B);
  ASSERT_TRUE(decOp.isComplete());

  CpuRegisters r;
  EXPECT_EQ(1, decOp.cycles());

  auto b = r.get(ByteRegister::B);
  *b = uint8_t(0x1); // 0001
  ASSERT_EQ(0x1, b->getByte());

  IMemoryViewSP m;
  decOp.execute(r, *m);
  EXPECT_EQ(0x0, r.get(ByteRegister::B)->getByte()); // 0000
}

TEST(ByteAluOperationTest, DecIndirect)
{
  ByteAluOperation decOp { ByteAluFunction::Dec, Source::Indirect };
  ASSERT_TRUE(decOp.isComplete());

  CpuRegisters r;
  EXPECT_EQ(3, decOp.cycles());

  *r.get(WordRegister::HL) = uint16_t(0x0100);

  TestBank m { { 0x0100, 0x0101 } };
  *m.getLocation(0x0100) = uint8_t(0x13);
  decOp.execute(r, m);
  EXPECT_EQ(0x12, m.getLocation(0x0100)->getByte());
}

TEST(ByteAluOperationTest, Throws)
{
  CpuRegisters r;
  IMemoryViewSP m;

  ByteAluOperation decOp { ByteAluFunction::Add, Source::Register };
  EXPECT_ANY_THROW(decOp.execute(r, *m));

  EXPECT_ANY_THROW(ByteAluOperation decOp2(ByteAluFunction::Add, Source::None));
}
