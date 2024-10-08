#include "gtest/gtest.h"

#include "cpu/operation/byteloadimmediate.h"
#include "cpu/operation/byteloadindirect.h"
#include "cpu/operation/byteloadoddball.h"
#include "cpu/operation/byteloadstandard.h"

#include "mock/testbank.h"

#include "cpu/cpuregisters.h"
#include "location/variablelocation.h"

TEST(ByteLoadTest, Immediate)
{
  ByteLoadImmediate loadImmediate { ByteRegister::L };
  EXPECT_FALSE(loadImmediate.isComplete());
  loadImmediate.nextOpcode(variableLocation(uint8_t(0x42)));
  ASSERT_TRUE(loadImmediate.isComplete());
  EXPECT_THROW(loadImmediate.nextOpcode(variableLocation(uint8_t(0x42))), std::logic_error);

  CpuRegisters r;
  EXPECT_EQ(2, loadImmediate.cycles());

  IMemoryViewSP m;
  loadImmediate.execute(r, *m);

  EXPECT_EQ(0x42, r.get(ByteRegister::L)->getByte());
}

TEST(ByteLoadTest, ImmediateIndirect)
{
  TestBank b({ 0, 2 });

  *b.getLocation(0, true) = uint16_t(0x0002);

  ByteLoadOddball loadImmediateIndirect { ByteLoadOddball::Direction::Indirect,
    ByteLoadOddball::Indirection::ImmediateStandard };
  EXPECT_FALSE(loadImmediateIndirect.isComplete());
  loadImmediateIndirect.nextOpcode(b.getLocation(0));
  EXPECT_FALSE(loadImmediateIndirect.isComplete());
  loadImmediateIndirect.nextOpcode(b.getLocation(1));
  ASSERT_TRUE(loadImmediateIndirect.isComplete());

  CpuRegisters r;
  EXPECT_EQ(4, loadImmediateIndirect.cycles());

  *r.get(ByteRegister::A) = uint8_t(0x42);
  loadImmediateIndirect.execute(r, b);

  EXPECT_EQ(0x42, b.getLocation(2)->getByte());
}

TEST(ByteLoadTest, ImmediateIndirect2)
{
  TestBank b({ 0xFF00, 0xFF02 });

  ByteLoadOddball loadImmediateIndirect2 { ByteLoadOddball::Direction::Register,
    ByteLoadOddball::Indirection::ImmediateZeroPage };
  EXPECT_FALSE(loadImmediateIndirect2.isComplete());
  loadImmediateIndirect2.nextOpcode(variableLocation(uint8_t(0x00)));
  ASSERT_TRUE(loadImmediateIndirect2.isComplete());

  CpuRegisters r;
  EXPECT_EQ(3, loadImmediateIndirect2.cycles());

  *b.getLocation(0xFF00) = uint8_t(0x42);
  loadImmediateIndirect2.execute(r, b);

  EXPECT_EQ(0x42, r.get(ByteRegister::A)->getByte());
}

TEST(ByteLoadTest, RegisterIndirect)
{
  TestBank m({ 0xDFFF, 0xDFFF });

  ByteLoadIndirect loadRI { ByteLoadIndirect::Direction::Indirect, ByteRegister::A, WordRegister::HL };
  ASSERT_TRUE(loadRI.isComplete());

  CpuRegisters r;
  EXPECT_EQ(2, loadRI.cycles());

  *r.get(WordRegister::HL) = uint16_t(0xDFFF);
  *r.get(ByteRegister::A) = uint8_t(0x3C);

  EXPECT_NE(0x3C, m.getLocation(0xDFFF)->getByte());
  loadRI.execute(r, m);
  EXPECT_EQ(0x3C, m.getLocation(0xDFFF)->getByte());
}

TEST(ByteLoadTest, RegisterIndirect2)
{
  TestBank m({ 0xDFFF, 0xDFFF });

  ByteLoadIndirect loadRI { ByteLoadIndirect::Direction::Register, ByteRegister::A, WordRegister::DE };
  ASSERT_TRUE(loadRI.isComplete());

  CpuRegisters r;
  EXPECT_EQ(2, loadRI.cycles());

  *r.get(WordRegister::DE) = uint16_t(0xDFFF);
  *r.get(ByteRegister::A) = uint8_t(0x3C);
  *m.getLocation(0xDFFF) = uint8_t(0xF3);
  loadRI.execute(r, m);

  EXPECT_EQ(0xF3, r.get(ByteRegister::A)->getByte());
}

TEST(ByteLoadTest, Post)
{
  TestBank m({ 0xDFFF, 0xDFFF });

  ByteLoadIndirect loadRI { ByteLoadIndirect::Direction::Register, ByteRegister::A, WordRegister::HL,
    ByteLoadIndirect::Post::Increment };
  ASSERT_TRUE(loadRI.isComplete());

  CpuRegisters r;
  *r.get(WordRegister::HL) = uint16_t(0xDFFF);
  *r.get(ByteRegister::A) = uint8_t(0x3C);

  *m.getLocation(0xDFFF) = uint8_t(0xF3);
  loadRI.execute(r, m);

  EXPECT_EQ(0xE000, r.get(WordRegister::HL)->getWord());
}

TEST(ByteLoadTest, Post2)
{
  TestBank m({ 0xDFFF, 0xDFFF });

  ByteLoadIndirect loadRI { ByteLoadIndirect::Direction::Indirect, ByteRegister::A, WordRegister::HL,
    ByteLoadIndirect::Post::Decrement };
  ASSERT_TRUE(loadRI.isComplete());

  CpuRegisters r;
  *r.get(WordRegister::HL) = uint16_t(0xDFFF);
  *r.get(ByteRegister::A) = uint8_t(0x3C);

  *m.getLocation(0xDFFF) = uint8_t(0xF3);
  loadRI.execute(r, m);

  EXPECT_EQ(0xDFFE, r.get(WordRegister::HL)->getWord());
}

TEST(ByteLoadTest, Post3)
{
  TestBank m({ 0xDFFF, 0xDFFF });

  ByteLoadIndirect loadRI { ByteLoadIndirect::Direction::Indirect, ByteRegister::A, WordRegister::HL,
    ByteLoadIndirect::Post::Increment };
  ASSERT_TRUE(loadRI.isComplete());

  CpuRegisters r;
  *r.get(WordRegister::HL) = uint16_t(0xDFFF);
  *r.get(ByteRegister::A) = uint8_t(0x3C);

  *m.getLocation(0xDFFF) = uint8_t(0xF3);
  loadRI.execute(r, m);

  EXPECT_EQ(0xE000, r.get(WordRegister::HL)->getWord());
}

TEST(ByteLoadTest, Post4)
{
  TestBank m({ 0xDFFF, 0xDFFF });

  ByteLoadIndirect loadRI { ByteLoadIndirect::Direction::Indirect, ByteRegister::A, WordRegister::HL,
    ByteLoadIndirect::Post::Decrement };
  ASSERT_TRUE(loadRI.isComplete());

  CpuRegisters r;
  *r.get(WordRegister::HL) = uint16_t(0xDFFF);
  *r.get(ByteRegister::A) = uint8_t(0x3C);

  *m.getLocation(0xDFFF) = uint8_t(0xF3);
  loadRI.execute(r, m);

  EXPECT_EQ(0xDFFE, r.get(WordRegister::HL)->getWord());
}
