#include "gtest/gtest.h"

#include "cpu/operation/wordload.h"

#include "cpu/cpuregisters.h"
#include "location/location.h"
#include "location/rambyte.h"
#include "location/variablebyte.h"
#include "mem/rambank.h"

TEST(WordLoadTest, Immediate)
{
  RamBank b({ 0, 1 });
  b.getWord(0).set(0x1C74);

  WordLoad loadImmediate { WordLoad::Destination::Register, WordLoad::Source::Immediate };
  loadImmediate.setDestination(WordRegister::DE);
  EXPECT_FALSE(loadImmediate.isComplete());
  loadImmediate.nextOpcode(b.getByte(0));
  EXPECT_FALSE(loadImmediate.isComplete());
  loadImmediate.nextOpcode(b.getByte(1));
  ASSERT_TRUE(loadImmediate.isComplete());

  EXPECT_THROW(loadImmediate.nextOpcode(b.getByte(1)), std::logic_error);

  CpuRegisters r;
  EXPECT_EQ(3, loadImmediate.cycles());

  IMemoryViewSP m;
  loadImmediate.execute(r, *m);
  auto value = r.get(WordRegister::DE).get();

  EXPECT_EQ(0x1C74, value);
}

TEST(WordLoadTest, Immediate2)
{
  RamBank b({ 0, 1 });
  b.getWord(0).set(0xDFFF);

  WordLoad loadImmediate { WordLoad::Destination::Register, WordLoad::Source::Immediate };
  loadImmediate.setDestination(WordRegister::HL);
  EXPECT_FALSE(loadImmediate.isComplete());
  loadImmediate.nextOpcode(b.getByte(0));
  EXPECT_FALSE(loadImmediate.isComplete());
  loadImmediate.nextOpcode(b.getByte(1));
  ASSERT_TRUE(loadImmediate.isComplete());

  CpuRegisters r;
  EXPECT_EQ(3, loadImmediate.cycles());

  IMemoryViewSP m;
  loadImmediate.execute(r, *m);
  auto value = r.get(WordRegister::HL).get();

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
  r.get(WordRegister::HL).set(value);

  ASSERT_NE(r.get(WordRegister::SP).get(), value);
  loadRegister.execute(r, *IMemoryViewSP());
  EXPECT_EQ(r.get(WordRegister::SP).get(), value);
}

TEST(WordLoadTest, ImmediateIndirect)
{
  RamBank b({ 0, 3 });
  b.getWord(0).set(0x0002);

  WordLoad loadIndirect { WordLoad::Destination::ImmediateIndirect, WordLoad::Source::Register };
  loadIndirect.setSource(WordRegister::HL);
  EXPECT_FALSE(loadIndirect.isComplete());
  loadIndirect.nextOpcode(b.getByte(0));
  EXPECT_FALSE(loadIndirect.isComplete());
  loadIndirect.nextOpcode(b.getByte(1));
  ASSERT_TRUE(loadIndirect.isComplete());

  CpuRegisters r;
  EXPECT_EQ(5, loadIndirect.cycles());

  r.get(WordRegister::HL).set(0xDFFF);
  loadIndirect.execute(r, b);

  EXPECT_EQ(0xDFFF, b.getWord(2).get());
}

TEST(WordLoadTest, RegisterIndirect)
{
  RamBank b({ 0, 3 });

  WordLoad loadIndirect { WordLoad::Destination::RegisterIndirect, WordLoad::Source::Register };
  loadIndirect.setSource(WordRegister::HL);
  loadIndirect.setDestination(WordRegister::AF);
  ASSERT_TRUE(loadIndirect.isComplete());

  CpuRegisters r;
  EXPECT_EQ(3, loadIndirect.cycles());

  r.get(WordRegister::HL).set(0xDFFF);
  r.get(WordRegister::AF).set(0x0002);
  loadIndirect.execute(r, b);

  EXPECT_EQ(0xDFFF, b.getWord(2).get());
}

TEST(WordLoadTest, Push)
{
  uint16_t value = 0xDFFF;
  CpuRegisters r;
  r.get(WordRegister::DE).set(value);
  r.get(WordRegister::SP).set(0x10);

  RamBank b { { 0x00, 0x10 } };

  WordLoad load { WordLoad::Destination::Stack, WordLoad::Source::Register };
  load.setSource(WordRegister::DE);
  ASSERT_TRUE(load.isComplete());

  EXPECT_EQ(4, load.cycles());

  load.execute(r, b);
  EXPECT_EQ(0x0E, r.get(WordRegister::SP).get());
  EXPECT_EQ(value, b.getWord(0x0E).get());
}

TEST(WordLoadTest, Pop)
{
  uint16_t value = 0xA1F5;
  CpuRegisters r;
  r.get(WordRegister::SP).set(0x0E);

  RamBank b { { 0x00, 0x10 } };
  b.getWord(0x0E).set(value);

  WordLoad load { WordLoad::Destination::Register, WordLoad::Source::Stack };
  load.setDestination(WordRegister::HL);
  ASSERT_TRUE(load.isComplete());

  EXPECT_EQ(3, load.cycles());

  load.execute(r, b);
  EXPECT_EQ(0x10, r.get(WordRegister::SP).get());
  EXPECT_EQ(value, b.getWord(0x0E).get());
}

TEST(WordLoadTest, RegisterImmediate)
{
  CpuRegisters r;
  r.get(WordRegister::SP).set(0x0F0E);

  RamBank b { { 0x00, 0x10 } };

  WordLoad load { WordLoad::Destination::Register, WordLoad::Source::RegisterImmediate };
  load.setDestination(WordRegister::SP);
  load.setSource(WordRegister::SP);
  EXPECT_FALSE(load.isComplete());
  load.nextOpcode(variableLocation(0x03));
  ASSERT_TRUE(load.isComplete());

  EXPECT_EQ(4, load.cycles());

  EXPECT_NO_THROW(load.execute(r, b));

  EXPECT_EQ(0x0F11, r.get(WordRegister::SP).get());
}

TEST(WordLoadTest, RegisterImmediate2)
{
  CpuRegisters r;
  r.get(WordRegister::SP).set(0x0F0E);
  r.get(WordRegister::HL).set(0xFFFF);

  RamBank b { { 0x00, 0x10 } };

  WordLoad load { WordLoad::Destination::Register, WordLoad::Source::RegisterImmediate };
  load.setDestination(WordRegister::HL);
  load.setSource(WordRegister::SP);
  EXPECT_FALSE(load.isComplete());
  load.nextOpcode(variableLocation(0x03));
  ASSERT_TRUE(load.isComplete());

  EXPECT_EQ(3, load.cycles());

  EXPECT_NO_THROW(load.execute(r, b));

  EXPECT_EQ(0x0F11, r.get(WordRegister::HL).get());
}
