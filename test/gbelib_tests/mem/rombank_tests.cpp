#include "gtest/gtest.h"

#include "location/location.h"
#include "mem/rombank.h"

TEST(RomBankTest, Indirect)
{
  uint8_t value = 0xA2;
  RomBank b({ 0, 15 }, std::vector<uint8_t>(16, value));
  EXPECT_ANY_THROW(b.getByte(4).set(value));
  EXPECT_EQ(value, b.getByte(4).get());
}
