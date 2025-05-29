#include "gtest/gtest.h"

#include "cpu/operation/pushpop.h"
#include "cpu/registers/cpuregisters.h"

#include "mock/testbank.h"

TEST(PushPopTest, Push)
{
  uint16_t value = 0xDFFFU;
  CpuRegisters r;
  r.get(WordRegister::DE) = value;
  r.get(WordRegister::SP) = uint16_t { 0x10U };

  TestBank b { { 0x00U, 0x10U } };

  PushPop pp { PushPop::Direction::Push, WordRegister::DE };
  ASSERT_TRUE(pp.isComplete());

  EXPECT_EQ(4, pp.cycles());

  pp.execute(r, b);
  EXPECT_EQ(0x0EU, r.get(WordRegister::SP).get());
  EXPECT_EQ(value, b.getLocation16(0x0EU).get());
}

TEST(PushPopTest, Pop)
{
  uint16_t value = 0xA1F5U;
  CpuRegisters r;
  r.get(WordRegister::SP) = uint16_t { 0x0EU };

  TestBank b { { 0x00U, 0x10U } };
  b.getLocation16(0x0EU) = value;

  PushPop pp { PushPop::Direction::Pop, WordRegister::HL };
  ASSERT_TRUE(pp.isComplete());

  EXPECT_EQ(3, pp.cycles());

  pp.execute(r, b);
  EXPECT_EQ(0x10U, r.get(WordRegister::SP).get());
  EXPECT_EQ(value, b.getLocation16(0x0EU).get());
}
