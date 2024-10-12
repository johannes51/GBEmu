#include "gtest/gtest.h"

#include "cpu/id/jumpscallsdecoder.h"

#include "cpu/operation/operation.h"
#include "location/variablelocation.h"

class JumpsCallsDecoderTest : public ::testing::Test {
public:
  JumpsCallsDecoderTest()
      : d()
  {
  }

protected:
  JumpsCallsDecoder d;
};

TEST_F(JumpsCallsDecoderTest, Opcodes)
{
  const auto opc = d.decodedOpcodes();

  EXPECT_EQ(30U, opc.size());
}

TEST_F(JumpsCallsDecoderTest, Direct)
{
  OperationUP op;
  EXPECT_NO_THROW(auto op = d.decode(*variableLocation(uint8_t { 0xC3U })));
  EXPECT_FALSE(op);
}

TEST_F(JumpsCallsDecoderTest, DirectZ)
{
  OperationUP op;
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0x20U })));
  EXPECT_TRUE(op);
}

TEST_F(JumpsCallsDecoderTest, DirectNZ)
{
  OperationUP op;
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0x28U })));
  EXPECT_TRUE(op);
}

TEST_F(JumpsCallsDecoderTest, DirectC)
{
  OperationUP op;
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0x30U })));
  EXPECT_TRUE(op);
}

TEST_F(JumpsCallsDecoderTest, DirectNC)
{
  OperationUP op;
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0x38U })));
  EXPECT_TRUE(op);
}

TEST_F(JumpsCallsDecoderTest, IndirectHL)
{
  OperationUP op;
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0xE9U })));
  EXPECT_TRUE(op);
}

TEST_F(JumpsCallsDecoderTest, Call)
{
  OperationUP op;
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0xCDU })));
  EXPECT_TRUE(op);
}

TEST_F(JumpsCallsDecoderTest, Return)
{
  OperationUP op;
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0xC8U })));
  EXPECT_TRUE(op);
}

TEST_F(JumpsCallsDecoderTest, Return2)
{
  OperationUP op;
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0xC9U })));
  EXPECT_TRUE(op);
}

TEST_F(JumpsCallsDecoderTest, ReturnI)
{
  OperationUP op;
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0xD9U })));
  EXPECT_TRUE(op);
}

TEST_F(JumpsCallsDecoderTest, Reset)
{
  OperationUP op;
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0xCFU })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0xDFU })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0xEFU })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0xFFU })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0xC7U })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0xD7U })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0xE7U })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0xF7U })));
  EXPECT_TRUE(op);
}
