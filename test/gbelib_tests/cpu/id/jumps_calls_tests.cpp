#include "gtest/gtest.h"

#include "cpu/id/jumpscallsdecoder.h"
#include "cpu/operation/operation.h"
#include "location/location.h"

#include "mock/variablebyte.h"

TEST(JumpsCallsDecoderTest, Direct)
{
  auto op = JumpsCallsDecoder {}.decode(variableLocation(0xC3));
  ASSERT_TRUE(op);
  EXPECT_FALSE(op->isComplete());
}
