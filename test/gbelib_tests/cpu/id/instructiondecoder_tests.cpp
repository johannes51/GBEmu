#include "gtest/gtest.h"

#include "cpu/id/instructiondecoder.h"
#include "cpu/operation/operation.h"
#include "location/location.h"

#include "debug/variablebyte.h"

TEST(InstructionDecoderTest, test00)
{
  auto nop = id::decode(Location<uint8_t>::generate(std::make_unique<VariableByte>(0x00)));
  EXPECT_TRUE(nop->isComplete());
}
