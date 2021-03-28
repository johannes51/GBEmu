#include "gtest/gtest.h"

#include "cpu/operation/byteload.h"

#include "cpu/cpuregisters.h"
#include "location/location.h"
#include "mem/rambank.h"

#include "mock/variablebyte.h"

TEST(ByteLoadTest, testImmediate)
{
  ByteLoad loadImmediate { ByteLoad::Destination::Register, ByteLoad::Source::Immediate };
  loadImmediate.setDestination(ByteRegisters::L);
  EXPECT_FALSE(loadImmediate.isComplete());
  loadImmediate.nextOpcode(Location<uint8_t>::generate(std::make_unique<VariableByte>(0x42)));
  ASSERT_TRUE(loadImmediate.isComplete());
  EXPECT_THROW(
      loadImmediate.nextOpcode(Location<uint8_t>::generate(std::make_unique<VariableByte>(0x42))), std::logic_error);

  EXPECT_EQ(2, loadImmediate.cycles());

  CpuRegisters r;
  IMemoryViewSP m;
  loadImmediate.execute(r, *m);

  EXPECT_EQ(0x42, r.get(ByteRegisters::L).get());
}

TEST(ByteLoadTest, testImmediateIndirect)
{
  RamBank b({ 0, 2 });

  ByteLoad loadImmediate { ByteLoad::Destination::ImmediateIndirect, ByteLoad::Source::Register };
  loadImmediate.setSource(ByteRegisters::A);
  EXPECT_FALSE(loadImmediate.isComplete());
  loadImmediate.nextOpcode(Location<uint8_t>::generate(std::make_unique<VariableByte>(0x00)));
  EXPECT_FALSE(loadImmediate.isComplete());
  loadImmediate.nextOpcode(Location<uint8_t>::generate(std::make_unique<VariableByte>(0x02)));
  ASSERT_TRUE(loadImmediate.isComplete());

  EXPECT_EQ(5, loadImmediate.cycles());

  CpuRegisters r;
  r.get(ByteRegisters::A).set(0x42);
  loadImmediate.execute(r, b);

  EXPECT_EQ(0x42, b.getByte(2).get());
}

TEST(ByteLoadTest, testRegisterIndirect)
{
  ByteLoad loadRI { ByteLoad::Destination::RegisterIndirect, ByteLoad::Source::Register };
  loadRI.setDestination(WordRegisters::HL);
  loadRI.setSource(ByteRegisters::A);
  ASSERT_TRUE(loadRI.isComplete());

  EXPECT_EQ(2, loadRI.cycles());

  CpuRegisters r;
  r.get(WordRegisters::HL).set(0xDFFF);
  r.get(ByteRegisters::A).set(0x3C);
  RamBank m({ 0xDFFF, 0xDFFF });
  loadRI.execute(r, m);

  EXPECT_EQ(0x3C, r.get(ByteRegisters::A).get());
}
