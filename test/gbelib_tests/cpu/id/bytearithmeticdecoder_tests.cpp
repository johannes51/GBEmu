#include "gtest/gtest.h"

#include "cpu/operation/operation.h"
#include "location/variablelocation.h"

#include "cpu/id/bytearithmeticdecoder.h"

class ByteArithmeticDecoderTest : public ::testing::Test {
public:
  ByteArithmeticDecoderTest()
      : d()
  {
  }

protected:
  ByteArithmeticDecoder d;
};

TEST_F(ByteArithmeticDecoderTest, Opcodes)
{
  auto opc = d.decodedOpcodes();
  EXPECT_EQ(88U, opc.size());
}

TEST_F(ByteArithmeticDecoderTest, Bulk)
{
  auto op = d.decode(*variableLocation(uint8_t { 0x80U }));
  ASSERT_TRUE(op);
  EXPECT_TRUE(op->isComplete());
}

TEST_F(ByteArithmeticDecoderTest, Unimplemented)
{
  OperationUP op;
  EXPECT_THROW(op = d.decode(*variableLocation(uint8_t { 0xC0U })), std::logic_error);
  ASSERT_FALSE(op);
}

TEST_F(ByteArithmeticDecoderTest, Sources)
{
  OperationUP op;
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0x87U })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0x80U })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0x81U })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0x82U })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0x83U })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0x84U })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0x85U })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0x35U })));
  EXPECT_TRUE(op);
}

TEST_F(ByteArithmeticDecoderTest, DestinationsIncDec)
{
  OperationUP op;
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0x04U })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0x14U })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0x24U })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0x34U })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0x0CU })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0x1CU })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0x2DU })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0x3DU })));
  EXPECT_TRUE(op);
}

TEST_F(ByteArithmeticDecoderTest, Functions)
{
  OperationUP op;
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0x83U })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0x93U })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0xA3U })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0xB3U })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0x88U })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0x98U })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0xA8U })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0xB8U })));
  EXPECT_TRUE(op);
}

TEST_F(ByteArithmeticDecoderTest, ImmediateFunctions)
{
  OperationUP op;
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0xC6U })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0xD6U })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0xE6U })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0xF6U })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0xCEU })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0xDEU })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0xEEU })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(*variableLocation(uint8_t { 0xFEU })));
  EXPECT_TRUE(op);
}
