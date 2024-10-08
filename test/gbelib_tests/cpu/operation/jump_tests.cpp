#include "gtest/gtest.h"

#include "cpu/cpuregisters.h"
#include "cpu/flagsview.h"
#include "cpu/operation/jump.h"
#include "location/location.h"
#include "location/variablelocation.h"
#include "mock/testbank.h"

TEST(JumpTest, Direct)
{
  CpuRegisters r;
  Jump jump { JumpType::Regular, TargetType::Absolute, Condition::None };

  EXPECT_FALSE(jump.isComplete());
  EXPECT_NO_THROW(jump.nextOpcode(variableLocation(uint16_t { 0x195E })));
  ASSERT_TRUE(jump.isComplete());

  EXPECT_EQ(4, jump.cycles());

  ASSERT_NE(0x195E, r.get(WordRegister::PC)->getWord());
  jump.execute(r, *IMemoryViewSP());
  EXPECT_EQ(0x195E, r.get(WordRegister::PC)->getWord());
}

TEST(JumpTest, Relative)
{
  CpuRegisters r;
  Jump jump { JumpType::Regular, TargetType::Relative, Condition::None };

  EXPECT_FALSE(jump.isComplete());
  EXPECT_NO_THROW(jump.nextOpcode(variableLocation(uint8_t { 0x1A })));
  ASSERT_TRUE(jump.isComplete());

  EXPECT_EQ(3, jump.cycles());

  *r.get(WordRegister::PC) = uint16_t { 0x1900 };
  jump.execute(r, *IMemoryViewSP());
  EXPECT_EQ(0x191A, r.get(WordRegister::PC)->getWord());
}

TEST(JumpTest, Z)
{
  Jump jump { JumpType::Regular, TargetType::Relative, Condition::Z };
  jump.nextOpcode(variableLocation(uint8_t { 0x1A }));

  CpuRegisters r;

  *r.get(WordRegister::PC) = uint16_t { 0x1900 };
  r.getFlags().setZero();

  EXPECT_FALSE(jump.isComplete());
  EXPECT_NO_THROW(jump.showFlags(r.getFlags()));
  EXPECT_TRUE(jump.isComplete());

  jump.execute(r, *IMemoryViewSP());
  EXPECT_EQ(0x191A, r.get(WordRegister::PC)->getWord());
  *r.get(WordRegister::PC) = uint16_t { 0x1900 };
  r.getFlags().clearZero();
  jump.showFlags(r.getFlags());
  jump.execute(r, *IMemoryViewSP());
  EXPECT_EQ(0x1900, r.get(WordRegister::PC)->getWord());
}

TEST(JumpTest, NZ)
{
  Jump jump { JumpType::Regular, TargetType::Relative, Condition::NZ };
  jump.nextOpcode(variableLocation(uint8_t { 0x1A }));

  CpuRegisters r;

  *r.get(WordRegister::PC) = uint16_t { 0x1900 };
  r.getFlags().clearZero();

  EXPECT_FALSE(jump.isComplete());
  EXPECT_NO_THROW(jump.showFlags(r.getFlags()));
  EXPECT_TRUE(jump.isComplete());

  jump.execute(r, *IMemoryViewSP());
  EXPECT_EQ(0x191A, r.get(WordRegister::PC)->getWord());
  *r.get(WordRegister::PC) = uint16_t { 0x1900 };
  r.getFlags().setZero();
  jump.showFlags(r.getFlags());
  jump.execute(r, *IMemoryViewSP());
  EXPECT_EQ(0x1900, r.get(WordRegister::PC)->getWord());
}

TEST(JumpTest, C)
{
  Jump jump { JumpType::Regular, TargetType::Relative, Condition::C };
  jump.nextOpcode(variableLocation(uint8_t { 0x1A }));

  CpuRegisters r;

  *r.get(WordRegister::PC) = uint16_t { 0x1900 };
  r.getFlags().setCarry();

  EXPECT_FALSE(jump.isComplete());
  EXPECT_NO_THROW(jump.showFlags(r.getFlags()));
  EXPECT_TRUE(jump.isComplete());

  jump.execute(r, *IMemoryViewSP());
  EXPECT_EQ(0x191A, r.get(WordRegister::PC)->getWord());
  *r.get(WordRegister::PC) = uint16_t { 0x1900 };
  r.getFlags().clearCarry();
  jump.showFlags(r.getFlags());
  jump.execute(r, *IMemoryViewSP());
  EXPECT_EQ(0x1900, r.get(WordRegister::PC)->getWord());
}

TEST(JumpTest, NC)
{
  Jump jump { JumpType::Regular, TargetType::Relative, Condition::NC };
  jump.nextOpcode(variableLocation(uint8_t { 0x1A }));

  CpuRegisters r;

  *r.get(WordRegister::PC) = uint16_t { 0x1900 };
  r.getFlags().clearCarry();

  EXPECT_FALSE(jump.isComplete());
  EXPECT_NO_THROW(jump.showFlags(r.getFlags()));
  EXPECT_TRUE(jump.isComplete());

  jump.execute(r, *IMemoryViewSP());
  EXPECT_EQ(0x191A, r.get(WordRegister::PC)->getWord());
  *r.get(WordRegister::PC) = uint16_t { 0x1900 };
  r.getFlags().setCarry();
  jump.showFlags(r.getFlags());
  jump.execute(r, *IMemoryViewSP());
  EXPECT_EQ(0x1900, r.get(WordRegister::PC)->getWord());
}

TEST(JumpTest, Next)
{
  CpuRegisters r;
  Jump jump { JumpType::Regular, TargetType::Absolute, Condition::None };

  EXPECT_FALSE(jump.isComplete());
  EXPECT_NO_THROW(jump.nextOpcode(variableLocation(uint16_t { 0x195E })));

  ASSERT_TRUE(jump.isComplete());
  EXPECT_THROW(jump.nextOpcode(variableLocation(uint8_t { 0x19 })), std::logic_error);
}

TEST(JumpTest, CallReturn)
{
  TestBank b { { 0x00, 0xFF } };
  CpuRegisters r;
  *r.get(WordRegister::PC) = uint16_t { 0xC300 };
  *r.get(WordRegister::SP) = uint16_t { 0x00FF };

  Jump call { JumpType::Call, TargetType::Absolute, Condition::None };
  ASSERT_NO_THROW(call.nextOpcode(variableLocation(uint16_t { 0xC3FE })));
  EXPECT_TRUE(call.isComplete());

  EXPECT_EQ(6, call.cycles());
  EXPECT_NO_THROW(call.execute(r, b));

  EXPECT_EQ(0xC3, b.getLocation(0xFE)->getByte());
  EXPECT_EQ(0x00, b.getLocation(0xFF)->getByte());
  EXPECT_EQ(0xC3FE, r.get(WordRegister::PC)->getWord());
  EXPECT_EQ(0xFD, r.get(WordRegister::SP)->getWord());

  Jump ret { JumpType::Return, TargetType::Absolute, Condition::None };
  EXPECT_TRUE(call.isComplete());
  EXPECT_EQ(4, ret.cycles());
  EXPECT_NO_THROW(ret.execute(r, b));

  EXPECT_EQ(0x00, b.getLocation(0xFD)->getByte());
  EXPECT_EQ(0xC3, b.getLocation(0xFE)->getByte());
  EXPECT_EQ(0xC300, r.get(WordRegister::PC)->getWord());
  EXPECT_EQ(0xFF, r.get(WordRegister::SP)->getWord());
}

TEST(JumpTest, RetZ)
{
  TestBank b { { 0x00, 0xFF } };
  CpuRegisters r;
  *r.get(WordRegister::PC) = uint16_t { 0xE001 };
  *r.get(WordRegister::SP) = uint16_t { 0xFD };
  *b.getLocation(0xFD) = uint16_t { 0xC003 };
  r.getFlags().clearZero();

  Jump ret { JumpType::Return, TargetType::Absolute, Condition::Z };

  EXPECT_FALSE(ret.isComplete());
  EXPECT_NO_THROW(ret.showFlags(r.getFlags()));
  EXPECT_TRUE(ret.isComplete());
  EXPECT_EQ(2, ret.cycles());
  EXPECT_NO_THROW(ret.execute(r, b));

  r.getFlags().setZero();
  EXPECT_NO_THROW(ret.showFlags(r.getFlags()));

  EXPECT_TRUE(ret.isComplete());
  EXPECT_EQ(5, ret.cycles());
  EXPECT_NO_THROW(ret.execute(r, b));

  EXPECT_EQ(0xC003, r.get(WordRegister::PC)->getWord());
  EXPECT_EQ(0xFF, r.get(WordRegister::SP)->getWord());
}

TEST(JumpTest, RetI)
{
  TestBank b { { 0x00, 0xFF } };
  CpuRegisters r;
  *r.get(WordRegister::PC) = uint16_t { 0x0C56 };
  *r.get(WordRegister::SP) = uint16_t { 0x00FD };
  *b.getLocation(0xFD) = uint16_t { 0xC003 };
  r.getFlags().disableInterrupt();

  Jump ret { JumpType::RetI, TargetType::Absolute, Condition::None };
  EXPECT_TRUE(ret.isComplete());
  EXPECT_EQ(4, ret.cycles());
  EXPECT_NO_THROW(ret.execute(r, b));

  EXPECT_EQ(0xC003, r.get(WordRegister::PC)->getWord());
  EXPECT_EQ(0xFF, r.get(WordRegister::SP)->getWord());
  EXPECT_TRUE(r.getFlags().interruptEnabled());
}

TEST(JumpTest, Reset)
{
  TestBank b { { 0x00, 0xFF } };
  CpuRegisters r;
  *r.get(WordRegister::PC) = uint16_t { 0xC300 };
  *r.get(WordRegister::SP) = uint16_t { 0x00FF };

  Jump call { JumpType::Reset, TargetType::Absolute, Condition::None };
  ASSERT_NO_THROW(call.nextOpcode(variableLocation(uint16_t { 0xC3FE })));
  EXPECT_TRUE(call.isComplete());
  EXPECT_EQ(4, call.cycles());
  EXPECT_NO_THROW(call.execute(r, b));

  EXPECT_EQ(0xC3, b.getLocation(0xFE)->getByte());
  EXPECT_EQ(0x00, b.getLocation(0xFF)->getByte());
  EXPECT_EQ(0xC3FE, r.get(WordRegister::PC)->getWord());
  EXPECT_EQ(0xFD, r.get(WordRegister::SP)->getWord());
}
