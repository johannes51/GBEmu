#include "gtest/gtest.h"

#include "cpu/operation/basicrotate.h"

#include "cpu/cpuregisters.h"

TEST(BasicRotateTest, Test1)
{
  CpuRegisters r;
  BasicRotate op { RotateDirection::Left, true };

  EXPECT_TRUE(op.isComplete());
  EXPECT_EQ(1U, op.cycles());

  EXPECT_NO_THROW(op.execute(r, *IMemoryViewSP()));
}

TEST(BasicRotateTest, Test2)
{
  CpuRegisters r;
  BasicRotate op { RotateDirection::Left, false };

  EXPECT_TRUE(op.isComplete());
  EXPECT_EQ(1U, op.cycles());

  EXPECT_NO_THROW(op.execute(r, *IMemoryViewSP()));
}

TEST(BasicRotateTest, Test3)
{
  CpuRegisters r;
  BasicRotate op { RotateDirection::Right, true };

  EXPECT_TRUE(op.isComplete());
  EXPECT_EQ(1U, op.cycles());

  EXPECT_NO_THROW(op.execute(r, *IMemoryViewSP()));
}

TEST(BasicRotateTest, Test4)
{
  CpuRegisters r;
  BasicRotate op { RotateDirection::Right, false };

  EXPECT_TRUE(op.isComplete());
  EXPECT_EQ(1U, op.cycles());

  EXPECT_NO_THROW(op.execute(r, *IMemoryViewSP()));
}
