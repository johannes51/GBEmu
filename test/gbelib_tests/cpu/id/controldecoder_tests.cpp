#include "gtest/gtest.h"

#include "cpu/id/controldecoder.h"
#include "cpu/operation/operation.h"

#include "mem/rest/variablelocation.h"

TEST(ControlDecoderTest, Construction) { EXPECT_NO_THROW(ControlDecoder d); }

TEST(ControlDecoderTest, DecodeNop)
{
  ControlDecoder d;
  EXPECT_NO_THROW(d.decode(variableLocation(uint8_t { 0x00U })));
}

TEST(ControlDecoderTest, DecodeEi)
{
  ControlDecoder d;
  EXPECT_NO_THROW(d.decode(variableLocation(uint8_t { 0xFBU })));
}

TEST(ControlDecoderTest, DecodeDi)
{
  ControlDecoder d;
  EXPECT_NO_THROW(d.decode(variableLocation(uint8_t { 0xF3U })));
}

TEST(ControlDecoderTest, DecodeStop)
{
  ControlDecoder d;
  EXPECT_NO_THROW(d.decode(variableLocation(uint8_t { 0x10U })));
}

TEST(ControlDecoderTest, DecodeHalt)
{
  ControlDecoder d;
  EXPECT_NO_THROW(d.decode(variableLocation(uint8_t { 0x76U })));
}

TEST(ControlDecoderTest, Exception)
{
  ControlDecoder d;
  EXPECT_ANY_THROW(d.decode(variableLocation(uint8_t { 0x80U })));
}
