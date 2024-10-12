#include "gtest/gtest.h"

#include "cpu/operation/miscarithmetic.h"

#include "cpu/cpuregisters.h"
#include "location/variablelocation.h"

TEST(MiscArithmeticTest, ComplementA)
{
  CpuRegisters r;
  MiscArithmetic op { MiscArithmeticFunction::ComplementA };

  EXPECT_TRUE(op.isComplete());
  EXPECT_EQ(1U, op.cycles());
  EXPECT_ANY_THROW(op.nextOpcode(variableLocation(uint8_t { 0x00U })));

  EXPECT_NO_THROW(op.execute(r, *IMemoryViewSP()));
}

TEST(MiscArithmeticTest, DecimalAdjustA)
{
  CpuRegisters r;
  MiscArithmetic op { MiscArithmeticFunction::DecimalAdjustA };

  EXPECT_TRUE(op.isComplete());
  EXPECT_EQ(1U, op.cycles());
  EXPECT_ANY_THROW(op.nextOpcode(variableLocation(uint8_t { 0x00U })));

  EXPECT_NO_THROW(op.execute(r, *IMemoryViewSP()));
}

TEST(MiscArithmeticTest, Carry)
{
  CpuRegisters r;
  MiscArithmetic op1 { MiscArithmeticFunction::SetCarry };
  MiscArithmetic op2 { MiscArithmeticFunction::ComplementCarry };

  EXPECT_TRUE(op1.isComplete());
  EXPECT_EQ(1U, op1.cycles());
  EXPECT_TRUE(op2.isComplete());
  EXPECT_EQ(1U, op2.cycles());

  r.getFlags().clearCarry();

  EXPECT_FALSE(r.getFlags().carry());
  EXPECT_NO_THROW(op1.execute(r, *IMemoryViewSP()));
  EXPECT_TRUE(r.getFlags().carry());
  EXPECT_NO_THROW(op1.execute(r, *IMemoryViewSP()));
  EXPECT_TRUE(r.getFlags().carry());

  EXPECT_NO_THROW(op2.execute(r, *IMemoryViewSP()));
  EXPECT_FALSE(r.getFlags().carry());
  EXPECT_NO_THROW(op2.execute(r, *IMemoryViewSP()));
  EXPECT_TRUE(r.getFlags().carry());
}
