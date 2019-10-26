#include "gtest/gtest.h"

#include "location/zerobyte.h"
#include "util/helpers.h"

TEST(HelperTest, testIndirect)
{
  EXPECT_EQ(address_type(0),
      hlp::indirect(Location<uint16_t>::generate(std::make_unique<ZeroByte>(), std::make_unique<ZeroByte>())));
}
