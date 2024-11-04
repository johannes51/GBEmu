#include "gtest/gtest.h"

#include "apu/channel_util/dac.h"

TEST(DACTests, Construction) { EXPECT_NO_THROW(DAC d {}); }

TEST(DACTests, Wav)
{
  DAC c;

  EXPECT_DOUBLE_EQ(0., c.getSample());

  c.set(0x0U);
  EXPECT_DOUBLE_EQ(1., c.getSample());

  c.set(0xFU);
  EXPECT_DOUBLE_EQ(-1., c.getSample());

  c.set(0xAU);
  EXPECT_LT(c.getSample(), 1.);
  EXPECT_GT(c.getSample(), -1.);
}
