#include "gtest/gtest.h"

#include "cpu/id/jumpscallsdecoder.h"
#include "cpu/operation/operation.h"
#include "location/location.h"

#include "mock/variablebyte.h"

TEST(JumpsCallsDecoderTest, Construction) { EXPECT_NO_THROW(JumpsCallsDecoder {}); }

TEST(JumpsCallsDecoderTest, Direct) { EXPECT_NO_THROW(auto op = JumpsCallsDecoder {}.decode(variableLocation(0xC3))); }

TEST(JumpsCallsDecoderTest, DirectZ) { EXPECT_NO_THROW(auto op = JumpsCallsDecoder {}.decode(variableLocation(0x20))); }

TEST(JumpsCallsDecoderTest, DirectNZ)
{
  EXPECT_NO_THROW(auto op = JumpsCallsDecoder {}.decode(variableLocation(0x28)));
}

TEST(JumpsCallsDecoderTest, DirectC) { EXPECT_NO_THROW(auto op = JumpsCallsDecoder {}.decode(variableLocation(0x30))); }

TEST(JumpsCallsDecoderTest, DirectNC)
{
  EXPECT_NO_THROW(auto op = JumpsCallsDecoder {}.decode(variableLocation(0x38)));
}

TEST(JumpsCallsDecoderTest, Call) { EXPECT_NO_THROW(auto op = JumpsCallsDecoder {}.decode(variableLocation(0xCD))); }

TEST(JumpsCallsDecoderTest, Return) { EXPECT_NO_THROW(auto op = JumpsCallsDecoder {}.decode(variableLocation(0xC9))); }
