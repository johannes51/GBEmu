#include "gtest/gtest.h"

#include "apu/channel_util/dac.h"

TEST(DACTests, Construction) { EXPECT_NO_THROW(DAC {}); }

TEST(DACTests, Wav)
{
  DAC d;

  EXPECT_DOUBLE_EQ(0., d.getSample());

  d.set(0x0U);
  EXPECT_DOUBLE_EQ(1., d.getSample());

  d.set(0xFU);
  EXPECT_DOUBLE_EQ(-1., d.getSample());

  d.set(0xAU);
  EXPECT_LT(d.getSample(), 1.);
  EXPECT_GT(d.getSample(), -1.);
}
