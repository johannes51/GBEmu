#include "gtest/gtest.h"

#include "cpu/cpuregisters.h"
#include "cpu/operation/wordaluoperation.h"
#include "location/location8.h"

TEST(WordAluOperationTest, Inc)
{
  CpuRegisters r;
  *r.get(WordRegister::DE) = uint16_t { 0xC3A1U };
  IMemoryViewSP m;

  WordAluOperation op { WordAluFunction::Inc, WordRegister::DE };
  ASSERT_TRUE(op.isComplete());
  EXPECT_EQ(2, op.cycles());

  EXPECT_NO_THROW(op.execute(r, *m));
  EXPECT_EQ(0xC3A2U, r.get(WordRegister::DE)->get());
}

TEST(WordAluOperationTest, Dec)
{
  CpuRegisters r;
  *r.get(WordRegister::HL) = uint16_t { 0xC3A1U };
  IMemoryViewSP m;

  WordAluOperation op { WordAluFunction::Dec, WordRegister::HL };
  ASSERT_TRUE(op.isComplete());
  EXPECT_EQ(2, op.cycles());

  EXPECT_NO_THROW(op.execute(r, *m));
  EXPECT_EQ(0xC3A0U, r.get(WordRegister::HL)->get());
}

TEST(WordAluOperationTest, Add)
{
  CpuRegisters r;
  *r.get(WordRegister::HL) = uint16_t { 0x0A09U };
  *r.get(WordRegister::BC) = uint16_t { 0x700AU };
  IMemoryViewSP m;

  WordAluOperation op { WordAluFunction::Add, WordRegister::BC };
  ASSERT_TRUE(op.isComplete());
  EXPECT_EQ(2, op.cycles());

  EXPECT_NO_THROW(op.execute(r, *m));
  EXPECT_EQ(0x7A13U, r.get(WordRegister::HL)->get());
}
