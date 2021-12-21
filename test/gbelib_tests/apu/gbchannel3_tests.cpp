#include "gtest/gtest.h"

#include "apu/gbchannel3.h"

TEST(GbChannel3Tests, Construction)
{
  EXPECT_NO_THROW(GbChannel3 c(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr));
}
