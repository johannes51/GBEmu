#include "gtest/gtest.h"

#include "cpu/operation/cbprefix.h"

#include "cpu/cpuregisters.h"
#include "cpu/id/controldecoder.h"
#include "location/variablelocation.h"

TEST(CbPrefixTest, Test)
{
  CpuRegisters r;
  CbPrefix op { std::make_unique<ControlDecoder>() };

  EXPECT_FALSE(op.isComplete());
  EXPECT_ANY_THROW(op.cycles());
  EXPECT_ANY_THROW(op.execute(r, *IMemoryViewSP()));

  op.nextOpcode(variableLocation(uint8_t { 0x00U })); // NOP

  EXPECT_TRUE(op.isComplete());
  EXPECT_EQ(1U, op.cycles());
  EXPECT_NO_THROW(op.execute(r, *IMemoryViewSP()));
}
