#include "gtest/gtest.h"

#include "util/helpers.h"

#include "debug/simplelocation.h"


using namespace std;

TEST(HelperTest, testIndirect) {
  auto a = Location<uint16_t>::generate(SimpleLocation(), SimpleLocation());
  ASSERT_EQ(address_type(0), hlp::indirect(a));
}

