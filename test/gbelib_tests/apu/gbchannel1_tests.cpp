#include "gtest/gtest.h"

#include "apu/gbchannel1.h"

TEST(GbChannel1Tests, Construction)
{
  EXPECT_NO_THROW(GbChannel1 c(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr));
}
