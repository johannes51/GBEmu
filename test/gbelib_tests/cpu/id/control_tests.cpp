#include "gtest/gtest.h"

#include "cpu/id/controldecoder.h"
#include "cpu/operation/operation.h"
#include "location/location.h"

#include "location/variablelocation.h"

TEST(ControlDecoderTest, Construction) { EXPECT_NO_THROW(ControlDecoder d); }

TEST(ControlDecoderTest, DecodeNop)
{
  ControlDecoder d;
  EXPECT_NO_THROW(d.decode(*variableLocation(uint8_t(0x00))));
}

TEST(ControlDecoderTest, DecodeEi)
{
  ControlDecoder d;
  EXPECT_NO_THROW(d.decode(*variableLocation(uint8_t(0xFB))));
}

TEST(ControlDecoderTest, DecodeDi)
{
  ControlDecoder d;
  EXPECT_NO_THROW(d.decode(*variableLocation(uint8_t(0xF3))));
}

TEST(ControlDecoderTest, Exception)
{
  ControlDecoder d;
  EXPECT_ANY_THROW(d.decode(*variableLocation(uint8_t(0x80))));
}
