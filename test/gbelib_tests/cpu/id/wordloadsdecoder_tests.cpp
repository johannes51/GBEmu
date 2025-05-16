#include "gtest/gtest.h"

#include "cpu/operation/operation.h"
#include "mem/rest/variablelocation.h"

#include "cpu/id/wordloadsdecoder.h"

class WordLoadsDecoderTest : public ::testing::Test {
public:
  WordLoadsDecoderTest()
      : d()
  {
  }

protected:
  WordLoadsDecoder d;
};

TEST_F(WordLoadsDecoderTest, Opcodes)
{
  auto opc = d.decodedOpcodes();
  ASSERT_EQ(16U, opc.size());
}

TEST_F(WordLoadsDecoderTest, Decode)
{
  OperationUP op;
  for (uint16_t opcode = 0x00U; opcode <= 0xFFU; ++opcode) {
    switch (opcode) {
    case 0x01U:
    case 0x11U:
    case 0x21U:
    case 0x31U:
    case 0x08U:
    case 0xE8U:
    case 0xF8U:
    case 0xF9U:
    case 0xC1U:
    case 0xD1U:
    case 0xE1U:
    case 0xF1U:
    case 0xC5U:
    case 0xD5U:
    case 0xE5U:
    case 0xF5U:
      EXPECT_NO_THROW(op = d.decode(variableLocation(static_cast<uint8_t>(opcode)))) << opcode;
      EXPECT_TRUE(op);
      break;
    default:
      break;
    }
    op.reset();
  }
  EXPECT_ANY_THROW(op = d.decode(variableLocation(uint8_t { 0xA4U })));
  EXPECT_FALSE(op);
}
