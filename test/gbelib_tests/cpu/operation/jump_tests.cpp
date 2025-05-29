#include "gtest/gtest.h"

#include "cpu/operation/jump.h"
#include "cpu/registers/cpuregisters.h"
#include "cpu/registers/flagsview.h"
#include "mem/ilocation8.h"
#include "mem/rest/variablelocation.h"
#include "mock/testbank.h"

TEST(JumpTest, Direct)
{
  CpuRegisters r;
  TestBank b { { 0x00U, 0x01U } };
  auto mem = TestBank { { .from = 0x0000, .to = 0xFFFF } };
  b.getLocation16(0x00U) = uint16_t { 0x195EU };
  Jump jump { JumpType::Regular, TargetType::Absolute, Condition::None };

  EXPECT_FALSE(jump.isComplete());
  EXPECT_NO_THROW(jump.nextOpcode(b.getLocation8(0x0U)));
  EXPECT_FALSE(jump.isComplete());
  EXPECT_NO_THROW(jump.nextOpcode(b.getLocation8(0x1U)));
  ASSERT_TRUE(jump.isComplete());
  EXPECT_NO_THROW(jump.showFlags(r.getFlags()));

  EXPECT_EQ(4, jump.cycles());

  ASSERT_NE(0x195EU, r.get(WordRegister::PC).get());
  jump.execute(r, mem);
  EXPECT_EQ(0x195EU, r.get(WordRegister::PC).get());
}

TEST(JumpTest, Relative)
{
  CpuRegisters r;
  Jump jump { JumpType::Regular, TargetType::Relative, Condition::None };
  auto mem = TestBank { { .from = 0x0000, .to = 0xFFFF } };

  EXPECT_FALSE(jump.isComplete());
  EXPECT_NO_THROW(jump.nextOpcode(variableLocation(uint8_t { 0x1AU })));
  ASSERT_TRUE(jump.isComplete());

  EXPECT_EQ(3, jump.cycles());

  r.get(WordRegister::PC) = uint16_t { 0x1900U };
  jump.execute(r, mem);
  EXPECT_EQ(0x191AU, r.get(WordRegister::PC).get());
}

TEST(JumpTest, Z)
{
  Jump jump { JumpType::Regular, TargetType::Relative, Condition::Z };
  auto mem = TestBank { { .from = 0x0000, .to = 0xFFFF } };

  CpuRegisters r;

  r.get(WordRegister::PC) = uint16_t { 0x1900U };
  r.getFlags().setZero();

  EXPECT_FALSE(jump.isComplete());

  EXPECT_ANY_THROW(jump.execute(r, mem));
  EXPECT_ANY_THROW(jump.cycles());
  EXPECT_NO_THROW(jump.showFlags(r.getFlags()));
  EXPECT_FALSE(jump.isComplete());

  EXPECT_ANY_THROW(jump.execute(r, mem));
  jump.nextOpcode(variableLocation(uint8_t { 0x1AU }));
  EXPECT_TRUE(jump.isComplete());

  jump.execute(r, mem);
  EXPECT_EQ(0x191AU, r.get(WordRegister::PC).get());
  r.get(WordRegister::PC) = uint16_t { 0x1900U };
  r.getFlags().clearZero();
  jump.showFlags(r.getFlags());
  jump.execute(r, mem);
  EXPECT_EQ(0x1900U, r.get(WordRegister::PC).get());
}

TEST(JumpTest, NZ)
{
  Jump jump { JumpType::Regular, TargetType::Relative, Condition::NZ };
  jump.nextOpcode(variableLocation(uint8_t { 0x1AU }));

  CpuRegisters r;
  auto mem = TestBank { { .from = 0x0000, .to = 0xFFFF } };

  r.get(WordRegister::PC) = uint16_t { 0x1900U };
  r.getFlags().clearZero();

  EXPECT_FALSE(jump.isComplete());
  EXPECT_NO_THROW(jump.showFlags(r.getFlags()));
  EXPECT_TRUE(jump.isComplete());

  jump.execute(r, mem);
  EXPECT_EQ(0x191AU, r.get(WordRegister::PC).get());
  r.get(WordRegister::PC) = uint16_t { 0x1900U };
  r.getFlags().setZero();
  jump.showFlags(r.getFlags());
  jump.execute(r, mem);
  EXPECT_EQ(0x1900U, r.get(WordRegister::PC).get());
}

TEST(JumpTest, C)
{
  Jump jump { JumpType::Regular, TargetType::Relative, Condition::C };
  jump.nextOpcode(variableLocation(uint8_t { 0x1AU }));

  CpuRegisters r;
  auto mem = TestBank { { .from = 0x0000, .to = 0xFFFF } };

  r.get(WordRegister::PC) = uint16_t { 0x1900U };
  r.getFlags().setCarry();

  EXPECT_FALSE(jump.isComplete());
  EXPECT_ANY_THROW(jump.execute(r, mem));
  EXPECT_ANY_THROW(jump.cycles());
  EXPECT_NO_THROW(jump.showFlags(r.getFlags()));
  EXPECT_TRUE(jump.isComplete());

  jump.execute(r, mem);
  EXPECT_EQ(0x191AU, r.get(WordRegister::PC).get());
  r.get(WordRegister::PC) = uint16_t { 0x1900U };
  r.getFlags().clearCarry();
  jump.showFlags(r.getFlags());
  jump.execute(r, mem);
  EXPECT_EQ(0x1900U, r.get(WordRegister::PC).get());
}

TEST(JumpTest, NC)
{
  Jump jump { JumpType::Regular, TargetType::Relative, Condition::NC };
  jump.nextOpcode(variableLocation(uint8_t { 0x1AU }));

  CpuRegisters r;
  auto mem = TestBank { { .from = 0x0000, .to = 0xFFFF } };

  r.get(WordRegister::PC) = uint16_t { 0x1900U };
  r.getFlags().clearCarry();

  EXPECT_FALSE(jump.isComplete());
  EXPECT_ANY_THROW(jump.execute(r, mem));
  EXPECT_ANY_THROW(jump.cycles());
  EXPECT_NO_THROW(jump.showFlags(r.getFlags()));
  EXPECT_TRUE(jump.isComplete());

  jump.execute(r, mem);
  EXPECT_EQ(0x191AU, r.get(WordRegister::PC).get());
  r.get(WordRegister::PC) = uint16_t { 0x1900U };
  r.getFlags().setCarry();
  jump.showFlags(r.getFlags());
  jump.execute(r, mem);
  EXPECT_EQ(0x1900U, r.get(WordRegister::PC).get());
}

TEST(JumpTest, AbsoluteZ)
{
  TestBank b({ 0U, 1U });
  Jump jump { JumpType::Regular, TargetType::Absolute, Condition::Z };

  b.getLocation16(0) = uint16_t { 0x1A1AU };

  CpuRegisters r;
  auto mem = TestBank { { .from = 0x0000, .to = 0xFFFF } };

  r.get(WordRegister::PC) = uint16_t { 0x1900U };
  r.getFlags().clearCarry();

  EXPECT_ANY_THROW(jump.execute(r, mem));
  EXPECT_NO_THROW(jump.showFlags(r.getFlags()));
  EXPECT_FALSE(jump.isComplete());
  EXPECT_ANY_THROW(jump.execute(r, mem));

  jump.nextOpcode(b.getLocation8((0U)));
  EXPECT_FALSE(jump.isComplete());
  EXPECT_ANY_THROW(jump.execute(r, mem));

  jump.nextOpcode(b.getLocation8(1U));
  EXPECT_TRUE(jump.isComplete());

  EXPECT_EQ(4U, jump.cycles());

  jump.execute(r, mem);
  EXPECT_EQ(0x1A1AU, r.get(WordRegister::PC).get());
}

TEST(JumpTest, Indirect)
{
  CpuRegisters r;
  auto mem = TestBank { { .from = 0x0000, .to = 0xFFFF } };
  Jump jump { JumpType::Indirect, TargetType::Absolute, Condition::None };

  EXPECT_TRUE(jump.isComplete());
  EXPECT_ANY_THROW(jump.nextOpcode(variableLocation(uint8_t { 0x5EU })));

  EXPECT_EQ(1U, jump.cycles());

  ASSERT_TRUE(jump.isComplete());
  EXPECT_THROW(jump.nextOpcode(variableLocation(uint8_t { 0x19U })), std::logic_error);

  r.get(WordRegister::HL) = uint16_t { 0x1234U };
  EXPECT_NO_THROW(jump.execute(r, mem));
  EXPECT_EQ(0x1234U, r.get(WordRegister::PC).get());
}

TEST(JumpTest, Next)
{
  CpuRegisters r;
  Jump jump { JumpType::Regular, TargetType::Absolute, Condition::None };

  EXPECT_FALSE(jump.isComplete());
  EXPECT_NO_THROW(jump.nextOpcode(variableLocation(uint8_t { 0x5EU })));
  EXPECT_FALSE(jump.isComplete());
  EXPECT_NO_THROW(jump.nextOpcode(variableLocation(uint8_t { 0x19U })));

  ASSERT_TRUE(jump.isComplete());
  EXPECT_THROW(jump.nextOpcode(variableLocation(uint8_t { 0x19U })), std::logic_error);
}

TEST(JumpTest, CallReturn)
{
  TestBank b { { 0x00U, 0xFFU } };
  CpuRegisters r;
  r.get(WordRegister::PC) = uint16_t { 0xC300U };
  r.get(WordRegister::SP) = uint16_t { 0x00FFU };

  Jump call { JumpType::Call, TargetType::Absolute, Condition::None };
  ASSERT_NO_THROW(call.nextOpcode(variableLocation(uint8_t { 0xFEU })));
  EXPECT_FALSE(call.isComplete());
  ASSERT_NO_THROW(call.nextOpcode(variableLocation(uint8_t { 0xC3U })));
  EXPECT_TRUE(call.isComplete());

  EXPECT_EQ(6, call.cycles());
  EXPECT_NO_THROW(call.execute(r, b));

  EXPECT_EQ(0xC3U, b.getLocation8(0xFEU).get());
  EXPECT_EQ(0x00U, b.getLocation8(0xFFU).get());
  EXPECT_EQ(0xC3FEU, r.get(WordRegister::PC).get());
  EXPECT_EQ(0xFDU, r.get(WordRegister::SP).get());

  Jump ret { JumpType::Return, TargetType::Absolute, Condition::None };
  EXPECT_TRUE(call.isComplete());
  EXPECT_EQ(4, ret.cycles());
  EXPECT_NO_THROW(ret.execute(r, b));

  EXPECT_EQ(0x00U, b.getLocation8(0xFDU).get());
  EXPECT_EQ(0xC3U, b.getLocation8(0xFEU).get());
  EXPECT_EQ(0xC300U, r.get(WordRegister::PC).get());
  EXPECT_EQ(0xFFU, r.get(WordRegister::SP).get());
}

TEST(JumpTest, RetZ)
{
  TestBank b { { 0x00U, 0xFFU } };
  CpuRegisters r;
  r.get(WordRegister::PC) = uint16_t { 0xE001U };
  r.get(WordRegister::SP) = uint16_t { 0xFDU };
  b.getLocation16(0xFDU) = uint16_t { 0xC003U };
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

  EXPECT_EQ(0xC003U, r.get(WordRegister::PC).get());
  EXPECT_EQ(0xFFU, r.get(WordRegister::SP).get());
}

TEST(JumpTest, RetI)
{
  TestBank b { { 0x00U, 0xFFU } };
  CpuRegisters r;
  r.get(WordRegister::PC) = uint16_t { 0x0C56U };
  r.get(WordRegister::SP) = uint16_t { 0x00FDU };
  b.getLocation16(0xFDU) = uint16_t { 0xC003U };
  r.getFlags().disableInterrupt();

  Jump ret { JumpType::RetI, TargetType::Absolute, Condition::None };
  EXPECT_TRUE(ret.isComplete());
  EXPECT_EQ(4, ret.cycles());
  EXPECT_NO_THROW(ret.execute(r, b));

  EXPECT_EQ(0xC003U, r.get(WordRegister::PC).get());
  EXPECT_EQ(0xFFU, r.get(WordRegister::SP).get());
  EXPECT_TRUE(r.getFlags().interruptEnabled());
}

TEST(JumpTest, Reset)
{
  TestBank b { { 0x00U, 0xFFU } };
  CpuRegisters r;
  r.get(WordRegister::PC) = uint16_t { 0xC300U };
  r.get(WordRegister::SP) = uint16_t { 0x00FFU };

  Jump call { JumpType::Reset, TargetType::Absolute, Condition::None };
  ASSERT_NO_THROW(call.nextOpcode(variableLocation(uint8_t { 0xFEU })));
  EXPECT_FALSE(call.isComplete());
  ASSERT_NO_THROW(call.nextOpcode(variableLocation(uint8_t { 0xC3U })));
  EXPECT_TRUE(call.isComplete());
  EXPECT_EQ(4, call.cycles());
  EXPECT_NO_THROW(call.execute(r, b));

  EXPECT_EQ(0xC3U, b.getLocation8(0xFEU).get());
  EXPECT_EQ(0x00U, b.getLocation8(0xFFU).get());
  EXPECT_EQ(0xC3FEU, r.get(WordRegister::PC).get());
  EXPECT_EQ(0xFDU, r.get(WordRegister::SP).get());
}
