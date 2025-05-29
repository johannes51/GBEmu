#include "gtest/gtest.h"

#include "mem/ilocation8.h"
#include "mem/rom/rombank.h"

TEST(RomBankTest, Indirect)
{
  uint8_t value = 0xA2;
  std::vector<uint8_t> v(16, value);
  RomBank b({ 0, 15 }, v);
  EXPECT_NO_THROW(b.getLocation8(4) = value);
  EXPECT_EQ(value, b.getLocation8(4).get());
}
