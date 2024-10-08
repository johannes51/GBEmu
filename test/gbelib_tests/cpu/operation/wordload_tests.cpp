#include "gtest/gtest.h"

#include "cpu/operation/wordload.h"
#include "cpu/cpuregisters.h"
#include "location/variablelocation.h"

#include "mock/testbank.h"

TEST(WordLoadTest, Immediate)
{
  TestBank b({ 0, 1 });
  *b.getLocation(0) = uint16_t(0x1C74);

  WordLoad loadImmediate { WordLoad::Destination::Register, WordLoad::Source::Immediate };
  loadImmediate.setDestination(WordRegister::DE);
  EXPECT_FALSE(loadImmediate.isComplete());
  loadImmediate.nextOpcode(b.getLocation(0, false));
  EXPECT_FALSE(loadImmediate.isComplete());
  loadImmediate.nextOpcode(b.getLocation(1));
  ASSERT_TRUE(loadImmediate.isComplete());

  EXPECT_THROW(loadImmediate.nextOpcode(b.getLocation(1)), std::logic_error);

  CpuRegisters r;
  EXPECT_EQ(3, loadImmediate.cycles());

  IMemoryViewSP m;
  loadImmediate.execute(r, *m);
  auto value = r.get(WordRegister::DE)->getWord();

  EXPECT_EQ(0x1C74, value);
}

TEST(WordLoadTest, Immediate2)
{
  TestBank b({ 0, 1 });
  *b.getLocation(0) = uint16_t(0xDFFF);

  WordLoad loadImmediate { WordLoad::Destination::Register, WordLoad::Source::Immediate };
  loadImmediate.setDestination(WordRegister::HL);
  EXPECT_FALSE(loadImmediate.isComplete());
  loadImmediate.nextOpcode(b.getLocation(0));
  EXPECT_FALSE(loadImmediate.isComplete());
  loadImmediate.nextOpcode(b.getLocation(1));
  ASSERT_TRUE(loadImmediate.isComplete());

  CpuRegisters r;
  EXPECT_EQ(3, loadImmediate.cycles());

  IMemoryViewSP m;
  loadImmediate.execute(r, *m);
  auto value = r.get(WordRegister::HL)->getWord();

  EXPECT_EQ(0xDFFF, value);
}

TEST(WordLoadTest, Register)
{
  WordLoad loadRegister { WordLoad::Destination::Register, WordLoad::Source::Register };
  loadRegister.setDestination(WordRegister::SP);
  loadRegister.setSource(WordRegister::HL);
  ASSERT_TRUE(loadRegister.isComplete());

  CpuRegisters r;
  EXPECT_EQ(2, loadRegister.cycles());

  uint16_t value = 0xDFFF;
  *r.get(WordRegister::HL) = value;

  ASSERT_NE(r.get(WordRegister::SP)->getWord(), value);
  loadRegister.execute(r, *IMemoryViewSP());
  EXPECT_EQ(r.get(WordRegister::SP)->getWord(), value);
}

TEST(WordLoadTest, ImmediateIndirect)
{
  TestBank b({ 0, 3 });
  *b.getLocation(0) = uint16_t(0x0002);

  WordLoad loadIndirect { WordLoad::Destination::ImmediateIndirect, WordLoad::Source::Register };
  loadIndirect.setSource(WordRegister::HL);
  EXPECT_FALSE(loadIndirect.isComplete());
  loadIndirect.nextOpcode(b.getLocation(0));
  EXPECT_FALSE(loadIndirect.isComplete());
  loadIndirect.nextOpcode(b.getLocation(1));
  ASSERT_TRUE(loadIndirect.isComplete());

  CpuRegisters r;
  EXPECT_EQ(5, loadIndirect.cycles());

  *r.get(WordRegister::HL) = uint16_t(0xDFFF);
  loadIndirect.execute(r, b);

  EXPECT_EQ(0xDFFF, b.getLocation(2)->getWord());
}

TEST(WordLoadTest, RegisterIndirect)
{
  TestBank b({ 0, 3 });

  WordLoad loadIndirect { WordLoad::Destination::RegisterIndirect, WordLoad::Source::Register };
  loadIndirect.setSource(WordRegister::HL);
  loadIndirect.setDestination(WordRegister::AF);
  ASSERT_TRUE(loadIndirect.isComplete());

  CpuRegisters r;
  EXPECT_EQ(3, loadIndirect.cycles());

  *r.get(WordRegister::HL) = uint16_t(0xDFFF);
  *r.get(WordRegister::AF) = uint16_t(0x0002);
  loadIndirect.execute(r, b);

  EXPECT_EQ(0xDFFF, b.getLocation(2)->getWord());
}

TEST(WordLoadTest, RegisterImmediate)
{
  CpuRegisters r;
  *r.get(WordRegister::SP) = uint16_t(0x0F0E);

  TestBank b { { 0x00, 0x10 } };

  WordLoad load { WordLoad::Destination::Register, WordLoad::Source::RegisterImmediate };
  load.setDestination(WordRegister::SP);
  load.setSource(WordRegister::SP);
  EXPECT_FALSE(load.isComplete());
  load.nextOpcode(variableLocation(uint8_t(0x03)));
  ASSERT_TRUE(load.isComplete());

  EXPECT_EQ(4, load.cycles());

  EXPECT_NO_THROW(load.execute(r, b));

  EXPECT_EQ(0x0F11, r.get(WordRegister::SP)->getWord());
}

TEST(WordLoadTest, RegisterImmediate2)
{
  CpuRegisters r;
  *r.get(WordRegister::SP) = uint16_t(0x0F0E);
  *r.get(WordRegister::HL) = uint16_t(0xFFFF);

  TestBank b { { 0x00, 0x10 } };

  WordLoad load { WordLoad::Destination::Register, WordLoad::Source::RegisterImmediate };
  load.setDestination(WordRegister::HL);
  load.setSource(WordRegister::SP);
  EXPECT_FALSE(load.isComplete());
  load.nextOpcode(variableLocation(uint8_t(0x03)));
  ASSERT_TRUE(load.isComplete());

  EXPECT_EQ(3, load.cycles());

  EXPECT_NO_THROW(load.execute(r, b));

  EXPECT_EQ(0x0F11, r.get(WordRegister::HL)->getWord());
}
