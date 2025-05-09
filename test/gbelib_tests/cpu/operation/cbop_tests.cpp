#include "gtest/gtest.h"

#include "cpu/operation/cbop.h"

#include "mock/testbank.h"

#include "cpu/cpuregisters.h"
#include "location/variablelocation.h"

TEST(CbOpTest, RotateRight)
{
  CpuRegisters r;
  CbOp op { CbOp::CbFunction::RotateRight, ByteRegister::A, false };
  *r.get(ByteRegister::A) = uint8_t { 0b10101010U };

  EXPECT_TRUE(op.isComplete());
  EXPECT_EQ(2U, op.cycles());
  EXPECT_ANY_THROW(op.nextOpcode(variableLocation(uint8_t { 0x00U })));

  EXPECT_NE(0b01010101U, r.get(ByteRegister::A)->get());
  EXPECT_NO_THROW(op.execute(r, *IMemoryViewSP()));
  EXPECT_EQ(0b01010101U, r.get(ByteRegister::A)->get());
}

TEST(CbOpTest, RotateRightCarry)
{
  CpuRegisters r;
  CbOp op { CbOp::CbFunction::RotateRightCarry, ByteRegister::A, false };

  EXPECT_TRUE(op.isComplete());
  EXPECT_EQ(2U, op.cycles());
  EXPECT_ANY_THROW(op.nextOpcode(variableLocation(uint8_t { 0x00U })));

  EXPECT_NO_THROW(op.execute(r, *IMemoryViewSP()));
}

TEST(CbOpTest, RotateLeft)
{
  CpuRegisters r;
  CbOp op { CbOp::CbFunction::RotateLeft, ByteRegister::A, false };

  EXPECT_TRUE(op.isComplete());
  EXPECT_EQ(2U, op.cycles());
  EXPECT_ANY_THROW(op.nextOpcode(variableLocation(uint8_t { 0x00U })));

  EXPECT_NO_THROW(op.execute(r, *IMemoryViewSP()));
}

TEST(CbOpTest, RotateLeftCarry)
{
  CpuRegisters r;
  CbOp op { CbOp::CbFunction::RotateLeftCarry, ByteRegister::A, false };

  EXPECT_TRUE(op.isComplete());
  EXPECT_EQ(2U, op.cycles());
  EXPECT_ANY_THROW(op.nextOpcode(variableLocation(uint8_t { 0x00U })));

  EXPECT_NO_THROW(op.execute(r, *IMemoryViewSP()));
}

TEST(CbOpTest, ShiftRightArithmetic)
{
  CpuRegisters r;
  CbOp op { CbOp::CbFunction::ShiftRightArithmetic, ByteRegister::A, false };

  EXPECT_TRUE(op.isComplete());
  EXPECT_EQ(2U, op.cycles());
  EXPECT_ANY_THROW(op.nextOpcode(variableLocation(uint8_t { 0x00U })));

  EXPECT_NO_THROW(op.execute(r, *IMemoryViewSP()));
}

TEST(CbOpTest, ShiftLeftArithmetic)
{
  CpuRegisters r;
  CbOp op { CbOp::CbFunction::ShiftLeftArithmetic, ByteRegister::A, false };

  EXPECT_TRUE(op.isComplete());
  EXPECT_EQ(2U, op.cycles());
  EXPECT_ANY_THROW(op.nextOpcode(variableLocation(uint8_t { 0x00U })));

  EXPECT_NO_THROW(op.execute(r, *IMemoryViewSP()));
}

TEST(CbOpTest, ShiftRightLogic)
{
  CpuRegisters r;
  CbOp op { CbOp::CbFunction::ShiftRightLogic, ByteRegister::A, false };

  EXPECT_TRUE(op.isComplete());
  EXPECT_EQ(2U, op.cycles());
  EXPECT_ANY_THROW(op.nextOpcode(variableLocation(uint8_t { 0x00U })));

  EXPECT_NO_THROW(op.execute(r, *IMemoryViewSP()));
}

TEST(CbOpTest, Swap)
{
  CpuRegisters r;
  TestBank b({ 0x0U, 0x1U });
  CbOp op { CbOp::CbFunction::Swap, ByteRegister::A, true };
  *r.get(WordRegister::HL) = uint16_t { 0x0000U };

  EXPECT_TRUE(op.isComplete());
  EXPECT_EQ(4U, op.cycles());
  EXPECT_ANY_THROW(op.nextOpcode(variableLocation(uint8_t { 0x00U })));

  EXPECT_NO_THROW(op.execute(r, b));
}

TEST(CbOpTest, Bit)
{
  CpuRegisters r;
  CbOp op { CbOp::CbFunction::Bit, ByteRegister::A, false };

  EXPECT_FALSE(op.isComplete());
  EXPECT_EQ(2U, op.cycles());
  EXPECT_ANY_THROW(op.nextOpcode(variableLocation(uint8_t { 0x00U })));

  EXPECT_ANY_THROW(op.setAffectedBit(8U));
  EXPECT_FALSE(op.isComplete());
  EXPECT_ANY_THROW(op.execute(r, *IMemoryViewSP()));

  EXPECT_NO_THROW(op.setAffectedBit(1U));
  EXPECT_TRUE(op.isComplete());

  EXPECT_NO_THROW(op.execute(r, *IMemoryViewSP()));
}

TEST(CbOpTest, Set)
{
  CpuRegisters r;
  CbOp op { CbOp::CbFunction::Set, ByteRegister::A, false };

  EXPECT_FALSE(op.isComplete());
  EXPECT_EQ(2U, op.cycles());
  EXPECT_ANY_THROW(op.nextOpcode(variableLocation(uint8_t { 0x00U })));

  EXPECT_ANY_THROW(op.setAffectedBit(8U));
  EXPECT_FALSE(op.isComplete());
  EXPECT_ANY_THROW(op.execute(r, *IMemoryViewSP()));

  EXPECT_NO_THROW(op.setAffectedBit(1U));
  EXPECT_TRUE(op.isComplete());

  EXPECT_NO_THROW(op.execute(r, *IMemoryViewSP()));
}

TEST(CbOpTest, Reset)
{
  CpuRegisters r;
  CbOp op { CbOp::CbFunction::Reset, ByteRegister::A, false };

  EXPECT_FALSE(op.isComplete());
  EXPECT_EQ(2U, op.cycles());
  EXPECT_ANY_THROW(op.nextOpcode(variableLocation(uint8_t { 0x00U })));

  EXPECT_ANY_THROW(op.setAffectedBit(8U));
  EXPECT_FALSE(op.isComplete());
  EXPECT_ANY_THROW(op.execute(r, *IMemoryViewSP()));

  EXPECT_NO_THROW(op.setAffectedBit(1U));
  EXPECT_TRUE(op.isComplete());

  EXPECT_NO_THROW(op.execute(r, *IMemoryViewSP()));
}
