#include "gtest/gtest.h"

#include "location/zerolocation.h"
#include "util/helpers.h"

TEST(HelperTest, Indirect) { EXPECT_EQ(address_type(0), hlp::indirect(*std::make_unique<ZeroLocation>())); }
