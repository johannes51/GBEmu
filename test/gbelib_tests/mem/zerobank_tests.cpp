#include "gtest/gtest.h"

#include "mem/ilocation8.h"
#include "mem/rest/zerobank.h"

using namespace std;

TEST(ZeroBankTest, Write)
{
  ZeroBank b { { 0, 16 } };
  address_type loc = 0x03;
  uint8_t value = 0xA2;

  b.getLocation8(loc) = value;

  EXPECT_EQ(0U, b.getLocation8(loc).get());
}
