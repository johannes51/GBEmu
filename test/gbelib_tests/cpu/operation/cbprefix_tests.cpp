#include "gtest/gtest.h"

#include "mock/testbank.h"

#include "cpu/operation/cbprefix.h"

#include "cpu/id/controldecoder.h"
#include "cpu/registers/cpuregisters.h"
#include "mem/rest/variablelocation.h"

TEST(CbPrefixTest, Test)
{
  CpuRegisters r;
  CbPrefix op { std::make_unique<ControlDecoder>() };

  auto mem = TestBank { MemoryArea { .from = 0x0000, .to = 0xFFFF } };

  EXPECT_FALSE(op.isComplete());
  EXPECT_ANY_THROW(op.cycles());
  EXPECT_ANY_THROW(op.execute(r, mem));

  op.nextOpcode(variableLocation(uint8_t { 0x00U })); // NOP

  EXPECT_TRUE(op.isComplete());
  EXPECT_EQ(1U, op.cycles());
  EXPECT_NO_THROW(op.execute(r, mem));
}
