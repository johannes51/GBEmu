#include "gtest/gtest.h"

#include "cpu/operation/operation.h"
#include "mem/rest/variablelocation.h"

#include "cpu/id/byteloadsdecoder.h"

class ByteLoadsDecoderTest : public ::testing::Test {
public:
  ByteLoadsDecoderTest()
      : d()
  {
  }

protected:
  ByteLoadsDecoder d;
};

TEST_F(ByteLoadsDecoderTest, Opcodes)
{
  auto opc = d.decodedOpcodes();
  ASSERT_EQ(85U, opc.size());
}

TEST_F(ByteLoadsDecoderTest, BulkLoad)
{
  auto op = d.decode(variableLocation(uint8_t { 0x42U }));
  ASSERT_TRUE(op);
  EXPECT_TRUE(op->isComplete());
  op = d.decode(variableLocation(uint8_t { 0x52U }));
  ASSERT_TRUE(op);
  EXPECT_TRUE(op->isComplete());
  op = d.decode(variableLocation(uint8_t { 0x62U }));
  ASSERT_TRUE(op);
  EXPECT_TRUE(op->isComplete());

  op = d.decode(variableLocation(uint8_t { 0x67U }));
  ASSERT_TRUE(op);
  EXPECT_TRUE(op->isComplete());
  op = d.decode(variableLocation(uint8_t { 0x68U }));
  ASSERT_TRUE(op);
  EXPECT_TRUE(op->isComplete());
  op = d.decode(variableLocation(uint8_t { 0x69U }));
  ASSERT_TRUE(op);
  EXPECT_TRUE(op->isComplete());
  op = d.decode(variableLocation(uint8_t { 0x6AU }));
  ASSERT_TRUE(op);
  EXPECT_TRUE(op->isComplete());
  op = d.decode(variableLocation(uint8_t { 0x6BU }));
  ASSERT_TRUE(op);
  EXPECT_TRUE(op->isComplete());
  op = d.decode(variableLocation(uint8_t { 0x6CU }));
  ASSERT_TRUE(op);
  EXPECT_TRUE(op->isComplete());
  op = d.decode(variableLocation(uint8_t { 0x6DU }));
  ASSERT_TRUE(op);
  EXPECT_TRUE(op->isComplete());
  op = d.decode(variableLocation(uint8_t { 0x6EU }));
  ASSERT_TRUE(op);
  EXPECT_TRUE(op->isComplete());
  op = d.decode(variableLocation(uint8_t { 0x6FU }));
  ASSERT_TRUE(op);
  EXPECT_TRUE(op->isComplete());

  op = d.decode(variableLocation(uint8_t { 0x36U }));
  ASSERT_TRUE(op);
  EXPECT_FALSE(op->isComplete());
}

TEST_F(ByteLoadsDecoderTest, ImmediateLoad)
{
  auto op = d.decode(variableLocation(uint8_t { 0x1EU }));
  ASSERT_TRUE(op);
  EXPECT_FALSE(op->isComplete());
}

TEST_F(ByteLoadsDecoderTest, RegInLoad)
{
  auto op = d.decode(variableLocation(uint8_t { 0x0AU }));
  ASSERT_TRUE(op);
  EXPECT_TRUE(op->isComplete());
  op = d.decode(variableLocation(uint8_t { 0x1AU }));
  ASSERT_TRUE(op);
  EXPECT_TRUE(op->isComplete());
  op = d.decode(variableLocation(uint8_t { 0x2AU }));
  ASSERT_TRUE(op);
  EXPECT_TRUE(op->isComplete());
  op = d.decode(variableLocation(uint8_t { 0x3AU }));
  ASSERT_TRUE(op);
  EXPECT_TRUE(op->isComplete());

  op = d.decode(variableLocation(uint8_t { 0x77U }));
  ASSERT_TRUE(op);
  EXPECT_TRUE(op->isComplete());
}

TEST_F(ByteLoadsDecoderTest, OddballLoad)
{
  auto op = d.decode(variableLocation(uint8_t { 0xE0U }));
  ASSERT_TRUE(op);
  EXPECT_FALSE(op->isComplete());
  op = d.decode(variableLocation(uint8_t { 0xE2U }));
  ASSERT_TRUE(op);
  EXPECT_TRUE(op->isComplete());
  op = d.decode(variableLocation(uint8_t { 0xEAU }));
  ASSERT_TRUE(op);
  EXPECT_FALSE(op->isComplete());
}
