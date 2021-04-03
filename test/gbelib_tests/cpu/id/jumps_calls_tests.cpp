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

TEST(JumpsCallsDecoderTest, DirectZ)
{
  auto op = JumpsCallsDecoder {}.decode(variableLocation(0x20));
  ASSERT_TRUE(op);
  EXPECT_FALSE(op->isComplete());
}

TEST(JumpsCallsDecoderTest, DirectNZ)
{
  auto op = JumpsCallsDecoder {}.decode(variableLocation(0x28));
  ASSERT_TRUE(op);
  EXPECT_FALSE(op->isComplete());
}

TEST(JumpsCallsDecoderTest, DirectC)
{
  auto op = JumpsCallsDecoder {}.decode(variableLocation(0x30));
  ASSERT_TRUE(op);
  EXPECT_FALSE(op->isComplete());
}

TEST(JumpsCallsDecoderTest, DirectNC)
{
  auto op = JumpsCallsDecoder {}.decode(variableLocation(0x38));
  ASSERT_TRUE(op);
  EXPECT_FALSE(op->isComplete());
}
