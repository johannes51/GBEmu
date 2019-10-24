#include "gtest/gtest.h"

#include "util/ops.h"
#include "location/location.h"
#include "location/rambyte.h"

TEST(OpsTest, testIncrement) {
  uint8_t buffer = 5;
  auto l = Location<uint8_t>::generate(std::make_unique<RamByte>(buffer));

  ops::increment(std::move(l));

  EXPECT_EQ(6, buffer);
}
