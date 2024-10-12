#include "gtest/gtest.h"

#include "cpu/id/unimplementeddecoder.h"

#include "cpu/operation/operation.h"
#include "location/variablelocation.h"

class UnimplementedDecoderTest : public ::testing::Test {
public:
  UnimplementedDecoderTest()
      : d()
  {
  }

protected:
  UnimplementedDecoder d;
};

TEST(UnimplementedDecoderTestNF, Construction) { EXPECT_NO_THROW(UnimplementedDecoder d); }

TEST_F(UnimplementedDecoderTest, Register) { EXPECT_EQ(11U, d.decodedOpcodes().size()); }

TEST_F(UnimplementedDecoderTest, Decode)
{
  OperationUP op;
  for (uint16_t opcode = 0x00U; opcode <= 0xFFU; ++opcode) {
    EXPECT_ANY_THROW(op = d.decode(*variableLocation(static_cast<uint8_t>(opcode))));
    EXPECT_FALSE(op);
  }
}
