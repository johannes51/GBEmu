#include "gtest/gtest.h"

#include "cpu/operation/operation.h"
#include "location/variablelocation.h"

#include "cpu/id/wordarithmeticdecoder.h"

class WordArithmeticDecoderTest : public ::testing::Test {
public:
  WordArithmeticDecoderTest()
      : d()
  {
  }

protected:
  WordArithmeticDecoder d;
};

TEST_F(WordArithmeticDecoderTest, Opcodes)
{
  auto opc = d.decodedOpcodes();
  EXPECT_EQ(12U, opc.size());
}

TEST_F(WordArithmeticDecoderTest, Unimplemented)
{
  OperationUP op;
  EXPECT_THROW(op = d.decode(*variableLocation(uint8_t { 0xC0U })), std::logic_error);
  ASSERT_FALSE(op);
  EXPECT_THROW(op = d.decode(*variableLocation(uint8_t { 0x3FU })), std::logic_error);
  ASSERT_FALSE(op);
}

TEST_F(WordArithmeticDecoderTest, Decode)
{
  OperationUP op;
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0x03U })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0x13U })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0x23U })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0x33U })));
  EXPECT_TRUE(op);

  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0x09U })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0x19U })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0x29U })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0x39U })));
  EXPECT_TRUE(op);

  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0x0BU })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0x1BU })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0x2BU })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0x3BU })));
  EXPECT_TRUE(op);
}
