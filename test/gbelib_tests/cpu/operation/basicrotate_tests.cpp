#include "gtest/gtest.h"

#include "mock/testbank.h"

#include "cpu/operation/basicrotate.h"

#include "cpu/cpuregisters.h"

TEST(BasicRotateTest, Test1)
{
  CpuRegisters r;
  BasicRotate op { RotateDirection::Left, true };
  auto mem = TestBank { { .from = 0x0000, .to = 0xFFFF } };

  EXPECT_TRUE(op.isComplete());
  EXPECT_EQ(1U, op.cycles());

  EXPECT_NO_THROW(op.execute(r, mem));
}

TEST(BasicRotateTest, Test2)
{
  CpuRegisters r;
  BasicRotate op { RotateDirection::Left, false };
  auto mem = TestBank { { .from = 0x0000, .to = 0xFFFF } };

  EXPECT_TRUE(op.isComplete());
  EXPECT_EQ(1U, op.cycles());

  EXPECT_NO_THROW(op.execute(r, mem));
}

TEST(BasicRotateTest, Test3)
{
  CpuRegisters r;
  BasicRotate op { RotateDirection::Right, true };
  auto mem = TestBank { { .from = 0x0000, .to = 0xFFFF } };

  EXPECT_TRUE(op.isComplete());
  EXPECT_EQ(1U, op.cycles());

  EXPECT_NO_THROW(op.execute(r, mem));
}

TEST(BasicRotateTest, Test4)
{
  CpuRegisters r;
  BasicRotate op { RotateDirection::Right, false };
  auto mem = TestBank { { .from = 0x0000, .to = 0xFFFF } };
  *r.get(ByteRegister::A) = 0b01010101U;

  EXPECT_TRUE(op.isComplete());
  EXPECT_EQ(1U, op.cycles());

  r.getFlags().clearCarry();
  r.getFlags().clearHalfCarry();
  r.getFlags().clearSubtract();
  r.getFlags().clearZero();

  EXPECT_NO_THROW(op.execute(r, mem));

  EXPECT_TRUE(r.getFlags().carry());
  EXPECT_FALSE(r.getFlags().halfCarry());
  EXPECT_FALSE(r.getFlags().subtract());
  EXPECT_FALSE(r.getFlags().zero());
}
