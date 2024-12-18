#include "gtest/gtest.h"

#include "location/location.h"
#include "mem/nullbank.h"

using namespace std;

TEST(NullBankTest, Write)
{
  NullBank b { { 0, 16 } };
  address_type loc = 0x03;
  uint8_t value = 0xA2;

  *b.getLocation(loc) = value;

  EXPECT_EQ(0U, b.getLocation(loc)->getByte());

  *b.getLocation(loc + 1U) = value;

  EXPECT_EQ(0U, b.getLocation(loc, true)->getWord());
}
