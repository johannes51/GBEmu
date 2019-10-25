#include "gtest/gtest.h"

#include "location/location.h"
#include "mem/nullbank.h"

using namespace std;

TEST(NullBankTest, testWrite) {
  NullBank b{{0, 16}};
  address_type loc = 0x03;
  uint8_t value = 0xA2;

  b.getByte(loc)->set(value);

  EXPECT_EQ(0, b.getByte(3)->get());
}
