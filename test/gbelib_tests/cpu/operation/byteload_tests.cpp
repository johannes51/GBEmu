#include "gtest/gtest.h"

#include "cpu/operation/byteload.h"

#include "cpu/cpuregisters.h"
#include "location/location.h"
#include "mem/rambank.h"

#include "mock/variablebyte.h"

TEST(ByteLoadTest, Immediate)
{
  ByteLoad loadImmediate { ByteLoad::Destination::Register, ByteLoad::Source::Immediate };
  loadImmediate.setDestination(ByteRegisters::L);
  EXPECT_FALSE(loadImmediate.isComplete());
  loadImmediate.nextOpcode(variableLocation(0x42));
  ASSERT_TRUE(loadImmediate.isComplete());
  EXPECT_THROW(loadImmediate.nextOpcode(variableLocation(0x42)), std::logic_error);

  CpuRegisters r;
  EXPECT_EQ(2, loadImmediate.cycles(r));

  IMemoryViewSP m;
  loadImmediate.execute(r, *m);

  EXPECT_EQ(0x42, r.get(ByteRegisters::L).get());
}

TEST(ByteLoadTest, ImmediateIndirect)
{
  RamBank b({ 0, 2 });

  ByteLoad loadImmediate { ByteLoad::Destination::ImmediateIndirect, ByteLoad::Source::Register };
  loadImmediate.setSource(ByteRegisters::A);
  EXPECT_FALSE(loadImmediate.isComplete());
  loadImmediate.nextOpcode(variableLocation(0x00));
  EXPECT_FALSE(loadImmediate.isComplete());
  loadImmediate.nextOpcode(variableLocation(0x02));
  ASSERT_TRUE(loadImmediate.isComplete());

  CpuRegisters r;
  EXPECT_EQ(4, loadImmediate.cycles(r));

  r.get(ByteRegisters::A).set(0x42);
  loadImmediate.execute(r, b);

  EXPECT_EQ(0x42, b.getByte(2).get());
}

TEST(ByteLoadTest, ImmediateIndirect2)
{
  RamBank b({ 0xFF00, 0xFF02 });

  ByteLoad loadImmediate { ByteLoad::Destination::Register, ByteLoad::Source::ImmediateIndirect, true };
  loadImmediate.setDestination(ByteRegisters::A);
  EXPECT_FALSE(loadImmediate.isComplete());
  loadImmediate.nextOpcode(variableLocation(0x00));
  ASSERT_TRUE(loadImmediate.isComplete());

  CpuRegisters r;
  EXPECT_EQ(3, loadImmediate.cycles(r));

  b.getByte(0xFF00).set(0x42);
  loadImmediate.execute(r, b);

  EXPECT_EQ(0x42, r.get(ByteRegisters::A).get());
}

TEST(ByteLoadTest, RegisterIndirect)
{
  ByteLoad loadRI { ByteLoad::Destination::RegisterIndirect, ByteLoad::Source::Register };
  loadRI.setDestination(WordRegisters::HL);
  loadRI.setSource(ByteRegisters::A);
  ASSERT_TRUE(loadRI.isComplete());

  CpuRegisters r;
  EXPECT_EQ(2, loadRI.cycles(r));

  r.get(WordRegisters::HL).set(0xDFFF);
  r.get(ByteRegisters::A).set(0x3C);
  RamBank m({ 0xDFFF, 0xDFFF });
  loadRI.execute(r, m);

  EXPECT_EQ(0x3C, m.getByte(0xDFFF).get());
}

TEST(ByteLoadTest, RegisterIndirect2)
{
  ByteLoad loadRI { ByteLoad::Destination::Register, ByteLoad::Source::RegisterIndirect };
  loadRI.setDestination(ByteRegisters::A);
  loadRI.setSource(WordRegisters::DE);
  ASSERT_TRUE(loadRI.isComplete());

  CpuRegisters r;
  EXPECT_EQ(2, loadRI.cycles(r));

  r.get(WordRegisters::DE).set(0xDFFF);
  r.get(ByteRegisters::A).set(0x3C);
  RamBank m({ 0xDFFF, 0xDFFF });
  m.getByte(0xDFFF).set(0xF3);
  loadRI.execute(r, m);

  EXPECT_EQ(0xF3, r.get(ByteRegisters::A).get());
}

TEST(ByteLoadTest, Post)
{
  ByteLoad loadRI { ByteLoad::Destination::Register, ByteLoad::Source::RegisterIndirect };
  loadRI.setDestination(ByteRegisters::A);
  loadRI.setSource(WordRegisters::HL);
  ASSERT_TRUE(loadRI.isComplete());

  EXPECT_NO_THROW(loadRI.setPostAction(ByteLoad::Post::Increment));

  CpuRegisters r;
  r.get(WordRegisters::HL).set(0xDFFF);
  r.get(ByteRegisters::A).set(0x3C);
  RamBank m({ 0xDFFF, 0xDFFF });
  m.getByte(0xDFFF).set(0xF3);
  loadRI.execute(r, m);

  r.get(ByteRegisters::A).get();
  EXPECT_EQ(0xE000, r.get(WordRegisters::HL).get());
}

TEST(ByteLoadTest, Post2)
{
  ByteLoad loadRI { ByteLoad::Destination::RegisterIndirect, ByteLoad::Source::Register };
  loadRI.setDestination(WordRegisters::HL);
  loadRI.setSource(ByteRegisters::A);
  ASSERT_TRUE(loadRI.isComplete());

  EXPECT_NO_THROW(loadRI.setPostAction(ByteLoad::Post::Decrement));

  CpuRegisters r;
  r.get(WordRegisters::HL).set(0xDFFF);
  r.get(ByteRegisters::A).set(0x3C);
  RamBank m({ 0xDFFF, 0xDFFF });
  m.getByte(0xDFFF).set(0xF3);
  loadRI.execute(r, m);

  r.get(ByteRegisters::A).get();
  EXPECT_EQ(0xDFFE, r.get(WordRegisters::HL).get());
}
