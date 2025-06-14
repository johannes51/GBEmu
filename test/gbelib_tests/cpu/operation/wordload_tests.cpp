#include "gtest/gtest.h"

#include "cpu/operation/wordload.h"
#include "cpu/registers/cpuregisters.h"
#include "mem/rest/variablelocation.h"

#include "mock/testbank.h"

TEST(WordLoadTest, Immediate)
{
  CpuRegisters r;
  auto mem = TestBank { { .from = 0x0000, .to = 0xFFFF } };
  TestBank b({ 0U, 1U });
  b.getLocation16(0U) = uint16_t { 0x1C74U };

  WordLoad loadImmediate { WordLoad::Destination::Register, WordLoad::Source::Immediate };
  loadImmediate.setDestination(WordRegister::DE);
  EXPECT_FALSE(loadImmediate.isComplete());

  EXPECT_ANY_THROW(loadImmediate.execute(r, b));

  loadImmediate.nextOpcode(b.getLocation8(0U));
  EXPECT_FALSE(loadImmediate.isComplete());
  loadImmediate.nextOpcode(b.getLocation8(1U));
  ASSERT_TRUE(loadImmediate.isComplete());

  EXPECT_THROW(loadImmediate.nextOpcode(b.getLocation8(1)), std::logic_error);

  EXPECT_EQ(3U, loadImmediate.cycles());

  loadImmediate.execute(r, mem);
  auto value = r.get(WordRegister::DE).get();

  EXPECT_EQ(0x1C74U, value);
}

TEST(WordLoadTest, Immediate2)
{
  auto mem = TestBank { { .from = 0x0000, .to = 0xFFFF } };
  TestBank b({ 0U, 1U });
  b.getLocation16(0U) = uint16_t { 0xDFFFU };

  WordLoad loadImmediate { WordLoad::Destination::Register, WordLoad::Source::Immediate };
  loadImmediate.setDestination(WordRegister::HL);
  EXPECT_FALSE(loadImmediate.isComplete());
  loadImmediate.nextOpcode(b.getLocation8(0));
  EXPECT_FALSE(loadImmediate.isComplete());
  loadImmediate.nextOpcode(b.getLocation8(1));
  ASSERT_TRUE(loadImmediate.isComplete());

  CpuRegisters r;
  EXPECT_EQ(3U, loadImmediate.cycles());

  loadImmediate.execute(r, mem);
  auto value = r.get(WordRegister::HL).get();

  EXPECT_EQ(0xDFFFU, value);
}

TEST(WordLoadTest, Register)
{
  auto mem = TestBank { { .from = 0x0000, .to = 0xFFFF } };
  WordLoad loadRegister { WordLoad::Destination::Register, WordLoad::Source::Register };
  loadRegister.setDestination(WordRegister::SP);
  loadRegister.setSource(WordRegister::HL);
  ASSERT_TRUE(loadRegister.isComplete());

  CpuRegisters r;
  EXPECT_EQ(2U, loadRegister.cycles());

  uint16_t value = 0xDFFFU;
  r.get(WordRegister::HL) = value;

  ASSERT_NE(r.get(WordRegister::SP).get(), value);
  loadRegister.execute(r, mem);
  EXPECT_EQ(r.get(WordRegister::SP).get(), value);
}

TEST(WordLoadTest, ImmediateIndirect)
{
  CpuRegisters r;
  TestBank b({ 0U, 3U });
  b.getLocation16(0U) = uint16_t { 0x0002U };

  WordLoad loadIndirect { WordLoad::Destination::ImmediateIndirect, WordLoad::Source::Register };
  loadIndirect.setSource(WordRegister::HL);

  EXPECT_ANY_THROW(loadIndirect.execute(r, b));

  EXPECT_FALSE(loadIndirect.isComplete());
  loadIndirect.nextOpcode(b.getLocation8(0U));
  EXPECT_FALSE(loadIndirect.isComplete());
  loadIndirect.nextOpcode(b.getLocation8(1U));
  ASSERT_TRUE(loadIndirect.isComplete());

  EXPECT_EQ(5U, loadIndirect.cycles());

  r.get(WordRegister::HL) = uint16_t { 0xDFFFU };
  loadIndirect.execute(r, b);

  EXPECT_EQ(0xDFFFU, b.getLocation16(2U).get());
}

TEST(WordLoadTest, RegisterIndirect)
{
  TestBank b({ 0U, 3U });

  WordLoad loadIndirect { WordLoad::Destination::RegisterIndirect, WordLoad::Source::Register };
  loadIndirect.setSource(WordRegister::HL);
  loadIndirect.setDestination(WordRegister::AF);
  ASSERT_TRUE(loadIndirect.isComplete());

  CpuRegisters r;
  EXPECT_EQ(3, loadIndirect.cycles());

  r.get(WordRegister::HL) = uint16_t { 0xDFFFU };
  r.get(WordRegister::AF) = uint16_t { 0x0002U };
  loadIndirect.execute(r, b);

  EXPECT_EQ(0xDFFFU, b.getLocation16(2U).get());
}

TEST(WordLoadTest, RegisterImmediate)
{
  CpuRegisters r;
  r.get(WordRegister::SP) = uint16_t { 0x0F0EU };

  TestBank b { { 0x00U, 0x10U } };

  WordLoad load { WordLoad::Destination::Register, WordLoad::Source::RegisterImmediate };
  load.setDestination(WordRegister::SP);
  load.setSource(WordRegister::SP);

  EXPECT_ANY_THROW(load.execute(r, b));

  EXPECT_FALSE(load.isComplete());
  load.nextOpcode(variableLocation(uint8_t { 0x03U }));
  ASSERT_TRUE(load.isComplete());

  EXPECT_EQ(4U, load.cycles());

  EXPECT_NO_THROW(load.execute(r, b));

  EXPECT_EQ(0x0F11U, r.get(WordRegister::SP).get());
}

TEST(WordLoadTest, RegisterImmediate2)
{
  CpuRegisters r;
  r.get(WordRegister::SP) = uint16_t { 0x0F0EU };
  r.get(WordRegister::HL) = uint16_t { 0xFFFFU };

  TestBank b { { 0x00U, 0x10U } };

  WordLoad load { WordLoad::Destination::Register, WordLoad::Source::RegisterImmediate };
  load.setDestination(WordRegister::HL);
  load.setSource(WordRegister::SP);
  EXPECT_FALSE(load.isComplete());
  load.nextOpcode(variableLocation(uint8_t { 0x03U }));
  ASSERT_TRUE(load.isComplete());

  EXPECT_EQ(3U, load.cycles());

  EXPECT_NO_THROW(load.execute(r, b));

  EXPECT_EQ(0x0F11U, r.get(WordRegister::HL).get());
}
