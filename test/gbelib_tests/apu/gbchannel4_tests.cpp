#include "gtest/gtest.h"

#include "apu/gbchannel4.h"

TEST(GbChannel4Tests, Construction) { EXPECT_NO_THROW(GbChannel4 c(nullptr, nullptr, nullptr, nullptr, nullptr)); }
