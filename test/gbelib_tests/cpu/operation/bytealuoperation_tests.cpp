#include "gtest/gtest.h"

#include "cpu/cpuregisters.h"
#include "cpu/operation/bytealuoperation.h"
#include "mem/location8.h"
#include "mock/testbank.h"

#include "mem/rest/variablelocation.h"

TEST(ByteAluOperationTest, AddImmediate)
{
  ByteAluOperation addOp { ByteAluFunction::AddCarry, Source::Immediate };
  ASSERT_FALSE(addOp.isComplete());
  ASSERT_NO_THROW(addOp.nextOpcode(variableLocation(uint8_t { 0x4DU })));
  ASSERT_TRUE(addOp.isComplete());
  ASSERT_ANY_THROW(addOp.nextOpcode(variableLocation(uint8_t { 0x4DU })));

  CpuRegisters r;
  EXPECT_EQ(2, addOp.cycles());

  r.get(ByteRegister::A) = uint8_t { 0x05U };

  IMemoryViewUP m = std::make_unique<TestBank>(MemoryArea { .from = 0x0000, .to = 0xFFFF });
  addOp.execute(r, *m);
  EXPECT_EQ(0x53U, r.get(ByteRegister::A).get());
}

TEST(ByteAluOperationTest, AddIndirect)
{
  ByteAluOperation addOp { ByteAluFunction::Add, Source::Indirect };
  ASSERT_TRUE(addOp.isComplete());
  EXPECT_ANY_THROW(addOp.nextOpcode(variableLocation(uint8_t { 0x4DU })));

  CpuRegisters r;
  EXPECT_EQ(2, addOp.cycles());

  r.get(ByteRegister::A) = uint8_t { 0x05U };
  r.get(WordRegister::HL) = uint16_t { 0x0100U };

  TestBank m { { 0x0100U, 0x0101U } };
  m.getLocation8(0x0100U) = uint8_t { 0x13U };
  addOp.execute(r, m);
  EXPECT_EQ(0x18U, r.get(ByteRegister::A).get());
}

TEST(ByteAluOperationTest, SubImmediate)
{
  ByteAluOperation addOp { ByteAluFunction::SubCarry, Source::Immediate };
  ASSERT_FALSE(addOp.isComplete());
  ASSERT_NO_THROW(addOp.nextOpcode(variableLocation(uint8_t { 0x4DU })));
  ASSERT_TRUE(addOp.isComplete());
  ASSERT_ANY_THROW(addOp.nextOpcode(variableLocation(uint8_t { 0x4DU })));

  CpuRegisters r;
  EXPECT_EQ(2, addOp.cycles());

  r.get(ByteRegister::A) = uint8_t { 0x4EU };

  IMemoryViewUP m = std::make_unique<TestBank>(MemoryArea { .from = 0x0000, .to = 0xFFFF });
  addOp.execute(r, *m);
  EXPECT_EQ(0x00U, r.get(ByteRegister::A).get());
}

TEST(ByteAluOperationTest, And)
{
  ByteAluOperation andOp { ByteAluFunction::And, Source::Register };
  andOp.setRegister(ByteRegister::B);
  ASSERT_TRUE(andOp.isComplete());

  CpuRegisters r;
  EXPECT_EQ(1, andOp.cycles());

  auto a = r.get(ByteRegister::A);
  a = uint8_t { 0x9U }; // 1001
  ASSERT_EQ(0x9U, a.get());
  auto b = r.get(ByteRegister::B);
  b = uint8_t { 0x5U }; // 0101
  ASSERT_EQ(0x5U, b.get());

  IMemoryViewUP m = std::make_unique<TestBank>(MemoryArea { .from = 0x0000, .to = 0xFFFF });
  andOp.execute(r, *m);
  EXPECT_EQ(0x1U, r.get(ByteRegister::A).get()); // 0001
}

TEST(ByteAluOperationTest, Or)
{
  ByteAluOperation orOp { ByteAluFunction::Or, Source::Register };
  orOp.setRegister(ByteRegister::B);
  ASSERT_TRUE(orOp.isComplete());

  CpuRegisters r;
  EXPECT_EQ(1, orOp.cycles());

  auto a = r.get(ByteRegister::A);
  a = uint8_t { 0x9U }; // 1001
  ASSERT_EQ(0x9U, a.get());
  auto b = r.get(ByteRegister::B);
  b = uint8_t { 0x5U }; // 0101
  ASSERT_EQ(0x5U, b.get());

  IMemoryViewUP m = std::make_unique<TestBank>(MemoryArea { .from = 0x0000, .to = 0xFFFF });
  orOp.execute(r, *m);
  EXPECT_EQ(0xDU, r.get(ByteRegister::A).get()); // 1100
}

TEST(ByteAluOperationTest, Xor)
{
  ByteAluOperation xorOp { ByteAluFunction::Xor, Source::Register };
  xorOp.setRegister(ByteRegister::B);
  ASSERT_TRUE(xorOp.isComplete());

  CpuRegisters r;
  EXPECT_EQ(1, xorOp.cycles());

  auto a = r.get(ByteRegister::A);
  a = uint8_t { 0x9U }; // 1001
  ASSERT_EQ(0x9U, a.get());
  auto b = r.get(ByteRegister::B);
  b = uint8_t { 0x5U }; // 0101
  ASSERT_EQ(0x5U, b.get());

  IMemoryViewUP m = std::make_unique<TestBank>(MemoryArea { .from = 0x0000, .to = 0xFFFF });
  xorOp.execute(r, *m);
  EXPECT_EQ(0xCU, r.get(ByteRegister::A).get()); // 1100
}

TEST(ByteAluOperationTest, Cp)
{
  ByteAluOperation cpOp { ByteAluFunction::Cp, Source::Register };
  cpOp.setRegister(ByteRegister::B);
  ASSERT_TRUE(cpOp.isComplete());

  CpuRegisters r;
  EXPECT_EQ(1, cpOp.cycles());

  auto a = r.get(ByteRegister::A);
  a = uint8_t { 0x9U }; // 1001
  ASSERT_EQ(0x9U, a.get());
  auto b = r.get(ByteRegister::B);
  b = uint8_t { 0xAU }; // 1010
  ASSERT_EQ(0xAU, b.get());

  IMemoryViewUP m = std::make_unique<TestBank>(MemoryArea { .from = 0x0000, .to = 0xFFFF });
  cpOp.execute(r, *m);
  EXPECT_EQ(0x9U, r.get(ByteRegister::A).get()); // 1100
  EXPECT_TRUE(r.getFlags().carry());
}

TEST(ByteAluOperationTest, Inc)
{
  ByteAluOperation decOp { ByteAluFunction::Inc, Source::Register };
  decOp.setRegister(ByteRegister::B);
  ASSERT_TRUE(decOp.isComplete());

  CpuRegisters r;
  EXPECT_EQ(1, decOp.cycles());

  auto b = r.get(ByteRegister::B);
  b = uint8_t { 0x1U }; // 0001
  ASSERT_EQ(0x1U, b.get());

  IMemoryViewUP m = std::make_unique<TestBank>(MemoryArea { .from = 0x0000, .to = 0xFFFF });
  decOp.execute(r, *m);
  EXPECT_EQ(0x2U, r.get(ByteRegister::B).get()); // 0010
}

TEST(ByteAluOperationTest, IncIndirect)
{
  ByteAluOperation decOp { ByteAluFunction::Inc, Source::Indirect };
  ASSERT_TRUE(decOp.isComplete());

  CpuRegisters r;
  EXPECT_EQ(3, decOp.cycles());

  r.get(WordRegister::HL) = uint16_t { 0x0100U };

  TestBank m { { 0x0100U, 0x0101U } };
  m.getLocation8(0x0100U) = uint8_t { 0x13U };
  decOp.execute(r, m);
  EXPECT_EQ(0x14U, m.getLocation8(0x0100U).get());
}

TEST(ByteAluOperationTest, Dec)
{
  ByteAluOperation decOp { ByteAluFunction::Dec, Source::Register };
  decOp.setRegister(ByteRegister::B);
  ASSERT_TRUE(decOp.isComplete());

  CpuRegisters r;
  EXPECT_EQ(1, decOp.cycles());

  auto b = r.get(ByteRegister::B);
  b = uint8_t { 0x1U }; // 0001
  ASSERT_EQ(0x1U, b.get());

  IMemoryViewUP m = std::make_unique<TestBank>(MemoryArea { .from = 0x0000, .to = 0xFFFF });
  decOp.execute(r, *m);
  EXPECT_EQ(0x0U, r.get(ByteRegister::B).get()); // 0000
}

TEST(ByteAluOperationTest, DecIndirect)
{
  ByteAluOperation decOp { ByteAluFunction::Dec, Source::Indirect };
  ASSERT_TRUE(decOp.isComplete());

  CpuRegisters r;
  EXPECT_EQ(3, decOp.cycles());

  r.get(WordRegister::HL) = uint16_t { 0x0100U };

  TestBank m { { 0x0100U, 0x0101U } };
  m.getLocation8(0x0100U) = uint8_t { 0x13U };
  decOp.execute(r, m);
  EXPECT_EQ(0x12U, m.getLocation8(0x0100U).get());
}

TEST(ByteAluOperationTest, Throws)
{
  CpuRegisters r;
  IMemoryViewUP m = std::make_unique<TestBank>(MemoryArea { .from = 0x0000, .to = 0xFFFF });

  ByteAluOperation decOp { ByteAluFunction::Add, Source::Register };
  EXPECT_ANY_THROW(decOp.execute(r, *m));

  EXPECT_ANY_THROW(ByteAluOperation decOp2(ByteAluFunction::Add, Source::None));

  ByteAluOperation decOp3(ByteAluFunction::Add, Source::Immediate);
  EXPECT_EQ(2U, decOp3.cycles());
  EXPECT_FALSE(decOp3.isComplete());
  EXPECT_ANY_THROW(decOp3.execute(r, *m));
}
