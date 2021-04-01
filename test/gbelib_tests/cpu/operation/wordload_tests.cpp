#include "gtest/gtest.h"

#include "cpu/operation/wordload.h"

#include "cpu/cpuregisters.h"
#include "location/location.h"
#include "location/rambyte.h"
#include "mem/rambank.h"

TEST(WordLoadTest, Immediate)
{
  RamBank b({ 0, 1 });
  b.getWord(0).set(0x1C74);

  WordLoad loadImmediate { WordLoad::Destination::Register, WordLoad::Source::Immediate };
  loadImmediate.setDestination(WordRegisters::DE);
  EXPECT_FALSE(loadImmediate.isComplete());
  loadImmediate.nextOpcode(b.getByte(0));
  EXPECT_FALSE(loadImmediate.isComplete());
  loadImmediate.nextOpcode(b.getByte(1));
  ASSERT_TRUE(loadImmediate.isComplete());

  EXPECT_THROW(loadImmediate.nextOpcode(b.getByte(1)), std::logic_error);

  CpuRegisters r;
  EXPECT_EQ(3, loadImmediate.cycles(r));

  IMemoryViewSP m;
  loadImmediate.execute(r, *m);
  auto value = r.get(WordRegisters::DE).get();

  EXPECT_EQ(0x1C74, value);
}

TEST(WordLoadTest, Immediate2)
{
  RamBank b({ 0, 1 });
  b.getWord(0).set(0xDFFF);

  WordLoad loadImmediate { WordLoad::Destination::Register, WordLoad::Source::Immediate };
  loadImmediate.setDestination(WordRegisters::HL);
  EXPECT_FALSE(loadImmediate.isComplete());
  loadImmediate.nextOpcode(b.getByte(0));
  EXPECT_FALSE(loadImmediate.isComplete());
  loadImmediate.nextOpcode(b.getByte(1));
  ASSERT_TRUE(loadImmediate.isComplete());

  CpuRegisters r;
  EXPECT_EQ(3, loadImmediate.cycles(r));

  IMemoryViewSP m;
  loadImmediate.execute(r, *m);
  auto value = r.get(WordRegisters::HL).get();

  EXPECT_EQ(0xDFFF, value);
}

TEST(WordLoadTest, Register)
{
  WordLoad loadRegister { WordLoad::Destination::Register, WordLoad::Source::Register };
  loadRegister.setDestination(WordRegisters::HL);
  loadRegister.setSource(WordRegisters::AF);
  ASSERT_TRUE(loadRegister.isComplete());

  CpuRegisters r;
  EXPECT_EQ(3, loadRegister.cycles(r));

  uint16_t value = 0xDFFF;
  r.get(WordRegisters::AF).set(value);

  ASSERT_NE(r.get(WordRegisters::HL).get(), value);
  loadRegister.execute(r, *IMemoryViewSP());
  EXPECT_EQ(r.get(WordRegisters::HL).get(), value);
}

TEST(WordLoadTest, ImmediateIndirect)
{
  RamBank b({ 0, 3 });
  b.getWord(0).set(0x0002);

  WordLoad loadIndirect { WordLoad::Destination::ImmediateIndirect, WordLoad::Source::Register };
  loadIndirect.setSource(WordRegisters::HL);
  EXPECT_FALSE(loadIndirect.isComplete());
  loadIndirect.nextOpcode(b.getByte(0));
  EXPECT_FALSE(loadIndirect.isComplete());
  loadIndirect.nextOpcode(b.getByte(1));
  ASSERT_TRUE(loadIndirect.isComplete());

  CpuRegisters r;
  EXPECT_EQ(5, loadIndirect.cycles(r));

  r.get(WordRegisters::HL).set(0xDFFF);
  loadIndirect.execute(r, b);

  EXPECT_EQ(0xDFFF, b.getWord(2).get());
}

TEST(WordLoadTest, RegisterIndirect)
{
  RamBank b({ 0, 3 });

  WordLoad loadIndirect { WordLoad::Destination::RegisterIndirect, WordLoad::Source::Register };
  loadIndirect.setSource(WordRegisters::HL);
  loadIndirect.setDestination(WordRegisters::AF);
  ASSERT_TRUE(loadIndirect.isComplete());

  CpuRegisters r;
  EXPECT_EQ(3, loadIndirect.cycles(r));

  r.get(WordRegisters::HL).set(0xDFFF);
  r.get(WordRegisters::AF).set(0x0002);
  loadIndirect.execute(r, b);

  EXPECT_EQ(0xDFFF, b.getWord(2).get());
}
