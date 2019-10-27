#include "gtest/gtest.h"

#include "cpu/operation/load.h"

#include "cpu/cpuregisters.h"
#include "location/location.h"

#include "debug/variablebyte.h"

TEST(LoadTest, testImmediate8)
{
  Load loadImmediate { Destination::Register8, Source::Immediate };
  loadImmediate.setDestination(ByteRegisters::L);
  EXPECT_FALSE(loadImmediate.isComplete());
  loadImmediate.nextOpcode(Location<uint8_t>::generate(std::make_unique<VariableByte>(0x42)));
  ASSERT_TRUE(loadImmediate.isComplete());

  EXPECT_FALSE(loadImmediate.isDone());
  EXPECT_NO_THROW(loadImmediate.clock());
  EXPECT_FALSE(loadImmediate.isDone());
  EXPECT_NO_THROW(loadImmediate.clock());
  ASSERT_TRUE(loadImmediate.isDone());

  CpuRegisters r;
  IMemoryViewSP m;
  loadImmediate.execute(r, *m);

  EXPECT_EQ(0x42, r.get(ByteRegisters::L).get());
}

TEST(LoadTest, testImmediate16)
{
  Load loadImmediate { Destination::Register16, Source::Immediate };
  loadImmediate.setDestination(WordRegisters::DE);
  EXPECT_FALSE(loadImmediate.isComplete());
  loadImmediate.nextOpcode(Location<uint8_t>::generate(std::make_unique<VariableByte>(0x1C)));
  EXPECT_FALSE(loadImmediate.isComplete());
  loadImmediate.nextOpcode(Location<uint8_t>::generate(std::make_unique<VariableByte>(0x74)));
  ASSERT_TRUE(loadImmediate.isComplete());

  EXPECT_FALSE(loadImmediate.isDone());
  EXPECT_NO_THROW(loadImmediate.clock());
  EXPECT_FALSE(loadImmediate.isDone());
  EXPECT_NO_THROW(loadImmediate.clock());
  EXPECT_FALSE(loadImmediate.isDone());
  EXPECT_NO_THROW(loadImmediate.clock());
  ASSERT_TRUE(loadImmediate.isDone());

  CpuRegisters r;
  IMemoryViewSP m;
  loadImmediate.execute(r, *m);

  EXPECT_EQ(0x741C, r.get(WordRegisters::DE).get());
}
