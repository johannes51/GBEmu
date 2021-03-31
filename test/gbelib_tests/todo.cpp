#include "gtest/gtest.h"

#include "cpu/id/controldecoder.h"
#include "cpu/id/jumpscallsdecoder.h"
#include "cpu/operation/operation.h"
#include "location/location.h"

#include "mock/variablebyte.h"

TEST(TodoTest, Unimplemented)
{
  EXPECT_ANY_THROW(JumpsCallsDecoder {}.decode(variableLocation(0x00)));
  EXPECT_ANY_THROW(ControlDecoder {}.decode(variableLocation(0x01)));
}
