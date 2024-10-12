#include "gtest/gtest.h"

#include "cpu/id/miscarithmeticdecoder.h"

#include "cpu/operation/operation.h"
#include "location/variablelocation.h"

class MiscArithmeticDecoderTest : public ::testing::Test {
public:
  MiscArithmeticDecoderTest()
      : d()
  {
  }

protected:
  MiscArithmeticDecoder d;
};

TEST(MiscArithmeticDecoderTestNF, Construction) { EXPECT_NO_THROW(MiscArithmeticDecoder d); }

TEST_F(MiscArithmeticDecoderTest, Register) { EXPECT_EQ(4U, d.decodedOpcodes().size()); }

TEST_F(MiscArithmeticDecoderTest, Decode)
{
  OperationUP op;
  for (uint16_t opcode = 0x00U; opcode <= 0xFFU; ++opcode) {
    switch (opcode) {
    case 0x27U:
    case 0x37U:
    case 0x2FU:
    case 0x3FU:
      EXPECT_NO_THROW(op = d.decode(*variableLocation(static_cast<uint8_t>(opcode))));
      EXPECT_TRUE(op);
      break;
    default:
      EXPECT_ANY_THROW(op = d.decode(*variableLocation(static_cast<uint8_t>(opcode))));
      EXPECT_FALSE(op);
      break;
    }
    op.reset();
  }
}
