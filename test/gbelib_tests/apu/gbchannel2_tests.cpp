#include "gtest/gtest.h"

#include "apu/gbchannel2.h"

TEST(GbChannel2Tests, Construction) { EXPECT_NO_THROW(GbChannel2 c(nullptr, nullptr, nullptr, nullptr, nullptr)); }
