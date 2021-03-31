#include "gtest/gtest.h"

#include "cpu/id/baseinstructiondecoder.h"
#include "cpu/id/controldecoder.h"
#include "cpu/operation/operation.h"
#include "location/location.h"

#include "mock/variablebyte.h"

TEST(BaseInstructionDecoderTest, Construction) { EXPECT_NO_THROW(BaseInstructionDecoder d); }

TEST(BaseInstructionDecoderTest, Register)
{
  BaseInstructionDecoder d;
  d.registerDecoder(std::make_shared<ControlDecoder>());
  EXPECT_EQ(3, d.decodedOpcodes().size());
}

TEST(BaseInstructionDecoderTest, Decode)
{
  BaseInstructionDecoder d;
  d.registerDecoder(std::make_shared<ControlDecoder>());
  EXPECT_NO_THROW(d.decode(variableLocation(0x00)));
}

TEST(BaseInstructionDecoderTest, Exception)
{
  BaseInstructionDecoder d;
  d.registerDecoder(std::make_shared<ControlDecoder>());
  EXPECT_ANY_THROW(d.decode(variableLocation(0x80)));
}
