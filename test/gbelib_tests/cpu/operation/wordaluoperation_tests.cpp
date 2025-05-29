#include "gtest/gtest.h"

#include "mock/testbank.h"

#include "cpu/operation/wordaluoperation.h"
#include "cpu/registers/cpuregisters.h"
#include "mem/ilocation8.h"

TEST(WordAluOperationTest, Inc)
{
  CpuRegisters r;
  auto mem = TestBank { { .from = 0x0000, .to = 0xFFFF } };
  r.get(WordRegister::DE) = uint16_t { 0xC3A1U };

  WordAluOperation op { WordAluFunction::Inc, WordRegister::DE };
  ASSERT_TRUE(op.isComplete());
  EXPECT_EQ(2, op.cycles());

  EXPECT_NO_THROW(op.execute(r, mem));
  EXPECT_EQ(0xC3A2U, r.get(WordRegister::DE).get());
}

TEST(WordAluOperationTest, Dec)
{
  CpuRegisters r;
  auto mem = TestBank { { .from = 0x0000, .to = 0xFFFF } };
  r.get(WordRegister::HL) = uint16_t { 0xC3A1U };

  WordAluOperation op { WordAluFunction::Dec, WordRegister::HL };
  ASSERT_TRUE(op.isComplete());
  EXPECT_EQ(2, op.cycles());

  EXPECT_NO_THROW(op.execute(r, mem));
  EXPECT_EQ(0xC3A0U, r.get(WordRegister::HL).get());
}

TEST(WordAluOperationTest, Add)
{
  CpuRegisters r;
  auto mem = TestBank { { .from = 0x0000, .to = 0xFFFF } };
  r.get(WordRegister::HL) = uint16_t { 0x0A09U };
  r.get(WordRegister::BC) = uint16_t { 0x700AU };

  WordAluOperation op { WordAluFunction::Add, WordRegister::BC };
  ASSERT_TRUE(op.isComplete());
  EXPECT_EQ(2, op.cycles());

  EXPECT_NO_THROW(op.execute(r, mem));
  EXPECT_EQ(0x7A13U, r.get(WordRegister::HL).get());
}
