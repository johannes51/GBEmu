#include "gtest/gtest.h"

#include "cpu/cpuregisters.h"
#include "cpu/operation/wordaluoperation.h"
#include "location/location.h"

TEST(WordAluOperationTest, Inc)
{
  CpuRegisters r;
  r.get(WordRegister::DE).set(0xC3A1);
  IMemoryViewSP m;

  WordAluOperation op { WordAluFunction::Inc, WordRegister::DE };
  ASSERT_TRUE(op.isComplete());
  EXPECT_EQ(2, op.cycles());

  EXPECT_NO_THROW(op.execute(r, *m));
  EXPECT_EQ(0xC3A2, r.get(WordRegister::DE).get());
}

TEST(WordAluOperationTest, Dec)
{
  CpuRegisters r;
  r.get(WordRegister::HL).set(0xC3A1);
  IMemoryViewSP m;

  WordAluOperation op { WordAluFunction::Dec, WordRegister::HL };
  ASSERT_TRUE(op.isComplete());
  EXPECT_EQ(2, op.cycles());

  EXPECT_NO_THROW(op.execute(r, *m));
  EXPECT_EQ(0xC3A0, r.get(WordRegister::HL).get());
}

TEST(WordAluOperationTest, Add)
{
  CpuRegisters r;
  r.get(WordRegister::HL).set(0x0A09);
  r.get(WordRegister::BC).set(0x700A);
  IMemoryViewSP m;

  WordAluOperation op { WordAluFunction::Add, WordRegister::BC };
  ASSERT_TRUE(op.isComplete());
  EXPECT_EQ(2, op.cycles());

  EXPECT_NO_THROW(op.execute(r, *m));
  EXPECT_EQ(0x7A13, r.get(WordRegister::HL).get());
}
