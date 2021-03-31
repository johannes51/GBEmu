#include "gtest/gtest.h"

#include "cpu/id/controldecoder.h"
#include "cpu/id/jumpscallsdecoder.h"
#include "cpu/operation/operation.h"
#include "location/location.h"

#include "mock/variablebyte.h"

TEST(TodoTest, Unimplemented)
{
  EXPECT_ANY_THROW(JumpsCallsDecoder {}.decode(Location<uint8_t>::generate(std::make_unique<VariableByte>(0x00))));
  EXPECT_ANY_THROW(ControlDecoder {}.decode(Location<uint8_t>::generate(std::make_unique<VariableByte>(0x01))));
}
