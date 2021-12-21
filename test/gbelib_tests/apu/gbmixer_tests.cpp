#include "gtest/gtest.h"

#include "apu/gbmixer.h"

TEST(GbMixerTests, Construction)
{
  EXPECT_NO_THROW(GbMixer m(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr));
}
