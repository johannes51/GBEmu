#include "gtest/gtest.h"

#include "cpu/cpuregisters.h"
#include "cpu/operation/aluoperation.h"
#include "location/location.h"

#include "debug/variablebyte.h"

TEST(AluOperationTest, testXor)
{
  AluOperation xorOp { AluFunction::Xor, Source::Register };
  xorOp.setRegister(ByteRegisters::B);
  ASSERT_TRUE(xorOp.isComplete());

  EXPECT_FALSE(xorOp.isDone());
  EXPECT_NO_THROW(xorOp.clock());
  ASSERT_TRUE(xorOp.isDone());

  CpuRegisters r;
  auto a = r.get(ByteRegisters::A);
  a.set(0x9); // 1001
  ASSERT_EQ(0x9, a.get());
  auto b = r.get(ByteRegisters::B);
  b.set(0x5); // 0101
  ASSERT_EQ(0x5, b.get());

  xorOp.execute(r);
  EXPECT_EQ(0xC, r.get(ByteRegisters::A).get()); // 1100
}
