#include "gtest/gtest.h"

#include "cpu/cpuregisters.h"
#include "cpu/operation/aluoperation.h"
#include "location/location.h"

#include "mock/variablebyte.h"

TEST(AluOperationTest, testXor)
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

TEST(AluOperationTest, testDec)
{
  AluOperation xorOp { AluFunction::Dec, Source::None };
  xorOp.setRegister(ByteRegisters::B);
  ASSERT_TRUE(xorOp.isComplete());

  EXPECT_EQ(1, xorOp.cycles());

  CpuRegisters r;
  auto b = r.get(ByteRegisters::B);
  b.set(0x5); // 0101
  ASSERT_EQ(0x5, b.get());

  IMemoryViewSP m;
  xorOp.execute(r, *m);
  EXPECT_EQ(0x4, r.get(ByteRegisters::B).get()); // 0100
}
