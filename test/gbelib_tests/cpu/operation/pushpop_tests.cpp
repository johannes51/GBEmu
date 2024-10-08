#include "gtest/gtest.h"

#include "cpu/operation/pushpop.h"
#include "cpu/cpuregisters.h"

#include "mock/testbank.h"

TEST(PushPopTest, Push)
{
  uint16_t value = 0xDFFF;
  CpuRegisters r;
  *r.get(WordRegister::DE) = uint16_t(value);
  *r.get(WordRegister::SP) = uint16_t(0x10);

  TestBank b { { 0x00, 0x10 } };

  PushPop pp { PushPop::Direction::Push, WordRegister::DE };
  ASSERT_TRUE(pp.isComplete());

  EXPECT_EQ(4, pp.cycles());

  pp.execute(r, b);
  EXPECT_EQ(0x0E, r.get(WordRegister::SP)->getWord());
  EXPECT_EQ(value, b.getLocation(0x0E)->getWord());
}

TEST(PushPopTest, Pop)
{
  uint16_t value = 0xA1F5;
  CpuRegisters r;
  *r.get(WordRegister::SP) = uint16_t(0x0E);

  TestBank b { { 0x00, 0x10 } };
  *b.getLocation(0x0E) = uint16_t(value);

  PushPop pp { PushPop::Direction::Pop, WordRegister::HL };
  ASSERT_TRUE(pp.isComplete());

  EXPECT_EQ(3, pp.cycles());

  pp.execute(r, b);
  EXPECT_EQ(0x10, r.get(WordRegister::SP)->getWord());
  EXPECT_EQ(value, b.getLocation(0x0E)->getWord());
}
