#include "gtest/gtest.h"

#include "cpu/id/baseinstructiondecoder.h"
#include "cpu/id/controldecoder.h"
#include "cpu/operation/operation.h"

#include "mem/rest/variablelocation.h"

class BaseInstructionDecoderTest : public ::testing::Test {
public:
  BaseInstructionDecoderTest()
      : d()
  {
  }

protected:
  BaseInstructionDecoder d;
};

TEST(BaseInstructionDecoderTestNF, Construction) { EXPECT_NO_THROW(BaseInstructionDecoder d); }

TEST_F(BaseInstructionDecoderTest, Register)
{
  d.registerDecoder(std::make_shared<ControlDecoder>());
  EXPECT_EQ(5, d.decodedOpcodes().size());
}

TEST_F(BaseInstructionDecoderTest, Decode)
{
  d.registerDecoder(std::make_shared<ControlDecoder>());
  EXPECT_NO_THROW(d.decode(variableLocation(uint8_t { 0x00U })));
}

TEST_F(BaseInstructionDecoderTest, UndecodedOpcode)
{
  d.registerDecoder(std::make_shared<ControlDecoder>());
  EXPECT_ANY_THROW(d.decode(variableLocation(uint8_t { 0x80U })));
}

TEST_F(BaseInstructionDecoderTest, AlreadyDecodedOpcode)
{
  d.registerDecoder(std::make_shared<ControlDecoder>());
  EXPECT_ANY_THROW(d.registerDecoder(std::make_shared<ControlDecoder>()));
}
