#include "gtest/gtest.h"

#include "util/ops.h"
#include "util/location.h"

#include "debug/simplelocation.h"


using namespace std;

TEST(OpsTest, testIndirect) {
  auto loc = Location<uint8_t>::generate(std::make_unique<SimpleLocation>());
  auto op = ops::toOperation(std::move(loc));

  ASSERT_EQ(0x0, op.lowerNibble());
  ASSERT_EQ(0x0, op.upperNibble());
}

