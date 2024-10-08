#include "gtest/gtest.h"

#include "location/location.h"
#include "mem/rombank.h"

TEST(RomBankTest, Indirect)
{
  uint8_t value = 0xA2;
  std::vector<uint8_t> v(16, value);
  RomBank b({ 0, 15 }, v);
  EXPECT_ANY_THROW(*b.getLocation(4) = uint8_t(value));
  EXPECT_EQ(value, b.getLocation(4)->getByte());
}
