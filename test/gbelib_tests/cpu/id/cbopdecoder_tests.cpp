#include "gtest/gtest.h"

#include "cpu/operation/operation.h"
#include "location/variablelocation.h"

#include "cpu/id/cbdecoder.h"
#include "cpu/id/cbopdecoder.h"

class CbOpDecoderTest : public ::testing::Test {
public:
  CbOpDecoderTest()
      : d1()
      , d2()
  {
  }

protected:
  CbDecoder d1;
  CbOpDecoder d2;
};

TEST_F(CbOpDecoderTest, Opcodes)
{
  auto opc = d1.decodedOpcodes();
  EXPECT_EQ(1U, opc.size());
  opc = d2.decodedOpcodes();
  EXPECT_EQ(0U, opc.size());
}

TEST_F(CbOpDecoderTest, CB)
{
  auto op = d1.decode(*variableLocation(uint8_t { 0xCBU }));
  ASSERT_TRUE(op);
  EXPECT_FALSE(op->isComplete());

  EXPECT_ANY_THROW(op = d1.decode(*variableLocation(uint8_t { 0xCCU })));
}

TEST_F(CbOpDecoderTest, CBOp)
{
  auto op = d1.decode(*variableLocation(uint8_t { 0xCBU }));
  ASSERT_TRUE(op);
  EXPECT_FALSE(op->isComplete());

  for (uint16_t opcode = 0x00U; opcode <= 0xFFU; ++opcode) {
    EXPECT_NO_THROW(op = d2.decode(*variableLocation(static_cast<uint8_t>(opcode)))) << opcode;
  }
}
