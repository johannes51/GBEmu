#include "gtest/gtest.h"

#include "cpu/id/basicrotatedecoder.h"

#include "cpu/operation/operation.h"
#include "mem/rest/variablelocation.h"

class BasicRotateDecoderTest : public ::testing::Test {
public:
  BasicRotateDecoderTest()
      : d()
  {
  }

protected:
  BasicRotateDecoder d;
};

TEST(BasicRotateDecoderTestNF, Construction) { EXPECT_NO_THROW(BasicRotateDecoder d); }

TEST_F(BasicRotateDecoderTest, Register) { EXPECT_EQ(4U, d.decodedOpcodes().size()); }

TEST_F(BasicRotateDecoderTest, Decode)
{
  OperationUP op;
  EXPECT_NO_THROW(op = d.decode(variableLocation(uint8_t { 0x07U })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(variableLocation(uint8_t { 0x0FU })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(variableLocation(uint8_t { 0x17U })));
  EXPECT_TRUE(op);
  EXPECT_NO_THROW(op = d.decode(variableLocation(uint8_t { 0x1FU })));
  EXPECT_TRUE(op);
}
