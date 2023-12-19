#include "gtest/gtest.h"

#include "cpu/id/baseinstructiondecoder.h"
#include "cpu/id/controldecoder.h"
#include "cpu/operation/operation.h"
#include "location/location.h"

#include "location/variablebyte.h"

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
  BaseInstructionDecoder d;
  d.registerDecoder(std::make_shared<ControlDecoder>());
  EXPECT_NO_THROW(d.decode(variableLocation(0x00)));
}

TEST_F(BaseInstructionDecoderTest, UndecodedOpcode)
{
  BaseInstructionDecoder d;
  d.registerDecoder(std::make_shared<ControlDecoder>());
  EXPECT_ANY_THROW(d.decode(variableLocation(0x80)));
}

TEST_F(BaseInstructionDecoderTest, AlreadyDecodedOpcode)
{
  BaseInstructionDecoder d;
  d.registerDecoder(std::make_shared<ControlDecoder>());
  EXPECT_ANY_THROW(d.registerDecoder(std::make_shared<ControlDecoder>()));
}
