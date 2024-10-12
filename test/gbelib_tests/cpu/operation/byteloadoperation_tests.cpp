#include "gtest/gtest.h"

#include "cpu/operation/byteloadimmediate.h"
#include "cpu/operation/byteloadindirect.h"
#include "cpu/operation/byteloadoddball.h"
#include "cpu/operation/byteloadstandard.h"

#include "mock/testbank.h"

#include "cpu/cpuregisters.h"
#include "location/variablelocation.h"

TEST(ByteLoadOperationTest, Immediate)
{
  ByteLoadImmediate loadImmediate { ByteRegister::L };
  EXPECT_FALSE(loadImmediate.isComplete());
  loadImmediate.nextOpcode(variableLocation(uint8_t { 0x42U }));
  ASSERT_TRUE(loadImmediate.isComplete());
  EXPECT_THROW(loadImmediate.nextOpcode(variableLocation(uint8_t { 0x42U })), std::logic_error);

  CpuRegisters r;
  EXPECT_EQ(2, loadImmediate.cycles());

  IMemoryViewSP m;
  loadImmediate.execute(r, *m);

  EXPECT_EQ(0x42U, r.get(ByteRegister::L)->getByte());
}

TEST(ByteLoadOperationTest, ImmediateIndirect)
{
  TestBank b({ 0, 2 });

  *b.getLocation(0, true) = uint16_t { 0x0002U };

  ByteLoadOddball loadImmediateIndirect { ByteLoadOddball::Direction::Indirect,
    ByteLoadOddball::Indirection::ImmediateStandard };
  EXPECT_FALSE(loadImmediateIndirect.isComplete());
  loadImmediateIndirect.nextOpcode(b.getLocation(0));
  EXPECT_FALSE(loadImmediateIndirect.isComplete());
  loadImmediateIndirect.nextOpcode(b.getLocation(1));
  ASSERT_TRUE(loadImmediateIndirect.isComplete());

  CpuRegisters r;
  EXPECT_EQ(4, loadImmediateIndirect.cycles());

  *r.get(ByteRegister::A) = uint8_t { 0x42U };
  loadImmediateIndirect.execute(r, b);

  EXPECT_EQ(0x42U, b.getLocation(2)->getByte());
}

TEST(ByteLoadOperationTest, ImmediateIndirect2)
{
  TestBank b({ 0xFF00U, 0xFF02U });

  ByteLoadOddball loadImmediateIndirect2 { ByteLoadOddball::Direction::Register,
    ByteLoadOddball::Indirection::ImmediateZeroPage };
  EXPECT_FALSE(loadImmediateIndirect2.isComplete());
  loadImmediateIndirect2.nextOpcode(variableLocation(uint8_t { 0x00U }));
  ASSERT_TRUE(loadImmediateIndirect2.isComplete());
  EXPECT_ANY_THROW(loadImmediateIndirect2.nextOpcode(variableLocation(uint8_t { 0x02U })););

  CpuRegisters r;
  EXPECT_EQ(3, loadImmediateIndirect2.cycles());

  *b.getLocation(0xFF00U) = uint8_t { 0x42U };
  loadImmediateIndirect2.execute(r, b);

  EXPECT_EQ(0x42U, r.get(ByteRegister::A)->getByte());
}

TEST(ByteLoadOperationTest, ImmediateRegisterIndirect)
{
  TestBank b({ 0xFF00U, 0xFF02U });
  CpuRegisters r;

  EXPECT_ANY_THROW(( ByteLoadImmediate(WordRegister::AF) ));

  ByteLoadImmediate loadImmediateRegisterIndirect { WordRegister::HL };
  EXPECT_FALSE(loadImmediateRegisterIndirect.isComplete());
  EXPECT_ANY_THROW(loadImmediateRegisterIndirect.execute(r, b));

  loadImmediateRegisterIndirect.nextOpcode(variableLocation(uint8_t { 0x02U }));
  ASSERT_TRUE(loadImmediateRegisterIndirect.isComplete());
  EXPECT_ANY_THROW(loadImmediateRegisterIndirect.nextOpcode(variableLocation(uint8_t { 0x02U })););

  EXPECT_EQ(3, loadImmediateRegisterIndirect.cycles());

  *b.getLocation(0xFF00U) = uint8_t { 0x42U };
  *r.get(WordRegister::HL) = uint16_t { 0xFF00U };
  loadImmediateRegisterIndirect.execute(r, b);

  EXPECT_EQ(0x02U, b.getLocation(0xFF00U)->getByte());
}

TEST(ByteLoadOperationTest, RegisterIndirect)
{
  TestBank m({ 0xDFFFU, 0xDFFFU });

  ByteLoadIndirect loadRI { ByteLoadIndirect::Direction::Indirect, ByteRegister::A, WordRegister::HL };
  ASSERT_TRUE(loadRI.isComplete());

  CpuRegisters r;
  EXPECT_EQ(2, loadRI.cycles());

  *r.get(WordRegister::HL) = uint16_t { 0xDFFFU };
  *r.get(ByteRegister::A) = uint8_t { 0x3CU };

  EXPECT_NE(0x3CU, m.getLocation(0xDFFFU)->getByte());
  loadRI.execute(r, m);
  EXPECT_EQ(0x3CU, m.getLocation(0xDFFFU)->getByte());
}

TEST(ByteLoadOperationTest, RegisterIndirect2)
{
  TestBank m({ 0xDFFFU, 0xDFFFU });

  ByteLoadIndirect loadRI { ByteLoadIndirect::Direction::Register, ByteRegister::A, WordRegister::DE };
  ASSERT_TRUE(loadRI.isComplete());

  CpuRegisters r;
  EXPECT_EQ(2, loadRI.cycles());

  *r.get(WordRegister::DE) = uint16_t { 0xDFFFU };
  *r.get(ByteRegister::A) = uint8_t { 0x3CU };
  *m.getLocation(0xDFFFU) = uint8_t { 0xF3U };
  loadRI.execute(r, m);

  EXPECT_EQ(0xF3U, r.get(ByteRegister::A)->getByte());
}

TEST(ByteLoadOperationTest, Post)
{
  TestBank m({ 0xDFFFU, 0xDFFFU });

  ByteLoadIndirect loadRI { ByteLoadIndirect::Direction::Register, ByteRegister::A, WordRegister::HL,
    ByteLoadIndirect::Post::Increment };
  ASSERT_TRUE(loadRI.isComplete());

  CpuRegisters r;
  *r.get(WordRegister::HL) = uint16_t { 0xDFFFU };
  *r.get(ByteRegister::A) = uint8_t { 0x3CU };

  *m.getLocation(0xDFFFU) = uint8_t { 0xF3U };
  loadRI.execute(r, m);

  EXPECT_EQ(0xE000U, r.get(WordRegister::HL)->getWord());
}

TEST(ByteLoadOperationTest, Post2)
{
  TestBank m({ 0xDFFFU, 0xDFFFU });

  ByteLoadIndirect loadRI { ByteLoadIndirect::Direction::Indirect, ByteRegister::A, WordRegister::HL,
    ByteLoadIndirect::Post::Decrement };
  ASSERT_TRUE(loadRI.isComplete());

  CpuRegisters r;
  *r.get(WordRegister::HL) = uint16_t { 0xDFFFU };
  *r.get(ByteRegister::A) = uint8_t { 0x3CU };

  *m.getLocation(0xDFFFU) = uint8_t { 0xF3U };
  loadRI.execute(r, m);

  EXPECT_EQ(0xDFFEU, r.get(WordRegister::HL)->getWord());
}

TEST(ByteLoadOperationTest, Post3)
{
  TestBank m({ 0xDFFFU, 0xDFFFU });

  ByteLoadIndirect loadRI { ByteLoadIndirect::Direction::Indirect, ByteRegister::A, WordRegister::HL,
    ByteLoadIndirect::Post::Increment };
  ASSERT_TRUE(loadRI.isComplete());

  CpuRegisters r;
  *r.get(WordRegister::HL) = uint16_t { 0xDFFFU };
  *r.get(ByteRegister::A) = uint8_t { 0x3CU };

  *m.getLocation(0xDFFFU) = uint8_t { 0xF3U };
  loadRI.execute(r, m);

  EXPECT_EQ(0xE000U, r.get(WordRegister::HL)->getWord());
}

TEST(ByteLoadOperationTest, Post4)
{
  TestBank m({ 0xDFFFU, 0xDFFFU });

  ByteLoadIndirect loadRI { ByteLoadIndirect::Direction::Indirect, ByteRegister::A, WordRegister::HL,
    ByteLoadIndirect::Post::Decrement };
  ASSERT_TRUE(loadRI.isComplete());

  CpuRegisters r;
  *r.get(WordRegister::HL) = uint16_t { 0xDFFFU };
  *r.get(ByteRegister::A) = uint8_t { 0x3CU };

  *m.getLocation(0xDFFFU) = uint8_t { 0xF3U };
  loadRI.execute(r, m);

  EXPECT_EQ(0xDFFEU, r.get(WordRegister::HL)->getWord());
}

TEST(ByteLoadOperationTest, RegisterC)
{
  TestBank m({ 0xFF00U, 0xFFFFU });

  ByteLoadOddball loadRI { ByteLoadOddball::Direction::Indirect, ByteLoadOddball::Indirection::RegisterC };
  EXPECT_TRUE(loadRI.isComplete());
  EXPECT_EQ(2U, loadRI.cycles());

  CpuRegisters r;
  *r.get(ByteRegister::C) = uint8_t { 0x42U };
  *r.get(ByteRegister::A) = uint8_t { 0x3CU };

  loadRI.execute(r, m);

  EXPECT_EQ(0x3CU, m.getLocation(0xFF42U)->getByte());
}

TEST(ByteLoadOperationTest, Standard)
{
  CpuRegisters r;

  ByteLoadStandard loadS { ByteRegister::C, ByteRegister::A };
  EXPECT_TRUE(loadS.isComplete());
  EXPECT_EQ(1U, loadS.cycles());

  *r.get(ByteRegister::C) = uint8_t { 0x42U };
  *r.get(ByteRegister::A) = uint8_t { 0x3CU };

  EXPECT_NE(0x3CU, r.get(ByteRegister::C)->getByte());
  loadS.execute(r, *IMemoryViewSP());
  EXPECT_EQ(0x3CU, r.get(ByteRegister::C)->getByte());
}
