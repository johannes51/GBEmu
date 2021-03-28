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

TEST(InstructionDecoderTest, testJump)
{
  auto op = id::decode(Location<uint8_t>::generate(std::make_unique<VariableByte>(0xC3)));
  EXPECT_NE(op, nullptr);
}

TEST(InstructionDecoderTest, testLoad)
{
  auto op = id::decode(Location<uint8_t>::generate(std::make_unique<VariableByte>(0x43)));
  EXPECT_NE(op, nullptr);
}

TEST(InstructionDecoderTest, testArith)
{
  auto op = id::decode(Location<uint8_t>::generate(std::make_unique<VariableByte>(0x83)));
  EXPECT_NE(op, nullptr);
}

TEST(InstructionDecoderTest, testUnknown)
{
  EXPECT_THROW(
      auto op = id::decode(Location<uint8_t>::generate(std::make_unique<VariableByte>(0xC4))), std::invalid_argument);
}

TEST(InstructionDecoderTest, testx0xTo3x1)
{
  auto op = id::decode(Location<uint8_t>::generate(std::make_unique<VariableByte>(0x06)));
  EXPECT_NE(op, nullptr);
}

TEST(InstructionDecoderTest, testx0xTo3x2)
{
  auto op = id::decode(Location<uint8_t>::generate(std::make_unique<VariableByte>(0x05)));
  EXPECT_NE(op, nullptr);
}

TEST(InstructionDecoderTest, testx0xTo3x3)
{
  auto op = id::decode(Location<uint8_t>::generate(std::make_unique<VariableByte>(0x02)));
  EXPECT_NE(op, nullptr);
}

TEST(InstructionDecoderTest, testx0xTo3x4)
{
  auto op = id::decode(Location<uint8_t>::generate(std::make_unique<VariableByte>(0x0A)));
  EXPECT_NE(op, nullptr);
}

TEST(InstructionDecoderTest, testx0xTo3x5)
{
  EXPECT_THROW(
      auto op = id::decode(Location<uint8_t>::generate(std::make_unique<VariableByte>(0x0F))), std::logic_error);
}
