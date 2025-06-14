#include "gtest/gtest.h"

#include "mem/ilocation8.h"
#include "mem/ram/rambank.h"

using namespace std;

TEST(RamBankTest, Write8)
{
  std::vector<uint8_t> v(16U);
  RamBank b({ 0U, 15U }, v);
  auto& writeByte = b.getLocation8(4);
  uint8_t value = 0xA2;
  writeByte = value;
  auto readByte = b.getLocation8(4).get();
  EXPECT_EQ(value, readByte);
}

TEST(RamBankTest, Oob)
{
  std::vector<uint8_t> v(2U);
  RamBank b({ 0, 1 }, v);
  EXPECT_THROW(b.getLocation8(4), std::invalid_argument);
}
