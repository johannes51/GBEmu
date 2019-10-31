#include "gtest/gtest.h"

#include "cpu/operation/wordload.h"

#include "cpu/cpuregisters.h"
#include "location/location.h"
#include "mem/rambank.h"

#include "debug/variablebyte.h"

TEST(WordLoadTest, testImmediate)
{
  RamBank b({0, 1});
  b.getWord(0).set(0x1C74);

  WordLoad loadImmediate { WordLoad::Destination::Register, WordLoad::Source::Immediate };
  loadImmediate.setDestination(WordRegisters::DE);
  EXPECT_FALSE(loadImmediate.isComplete());
  loadImmediate.nextOpcode(b.getByte(0));
  EXPECT_FALSE(loadImmediate.isComplete());
  loadImmediate.nextOpcode(b.getByte(1));
  ASSERT_TRUE(loadImmediate.isComplete());

  EXPECT_EQ(3, loadImmediate.cycles());

  CpuRegisters r;
  IMemoryViewSP m;
  loadImmediate.execute(r, *m);
  auto value = r.get(WordRegisters::DE).get();

  EXPECT_EQ(0x1C74, value);
}

TEST(WordLoadTest, testImmediate2)
{
  RamBank b({0, 1});
  b.getWord(0).set(0xDFFF);

  WordLoad loadImmediate { WordLoad::Destination::Register, WordLoad::Source::Immediate };
  loadImmediate.setDestination(WordRegisters::HL);
  EXPECT_FALSE(loadImmediate.isComplete());
  loadImmediate.nextOpcode(b.getByte(0));
  EXPECT_FALSE(loadImmediate.isComplete());
  loadImmediate.nextOpcode(b.getByte(1));
  ASSERT_TRUE(loadImmediate.isComplete());

  EXPECT_EQ(3, loadImmediate.cycles());

  CpuRegisters r;
  IMemoryViewSP m;
  loadImmediate.execute(r, *m);
  auto value = r.get(WordRegisters::HL).get();

  EXPECT_EQ(0xDFFF, value);
}
