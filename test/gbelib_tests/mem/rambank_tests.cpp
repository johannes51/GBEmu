#include "gtest/gtest.h"

#include "location/location.h"
#include "mem/rambank.h"

using namespace std;

TEST(RamBankTest, Write8)
{
  std::vector<uint8_t> v{16U};
  RamBank b({ 0, 16 }, v);
  auto writeByte = b.getLocation(4);
  uint8_t value = 0xA2;
  *writeByte = value;
  auto readByte = b.getLocation(4)->getByte();
  EXPECT_EQ(value, readByte);
}

TEST(RamBankTest, Write16)
{
  std::vector<uint8_t> v(16U);
  RamBank b({ 0, 16 }, v);
  auto writeWord = b.getLocation(4, true);
  uint16_t value = 0xA27E;
  *writeWord = value;
  auto readWord = b.getLocation(4)->getWord();
  EXPECT_EQ(value, readWord);
}

TEST(RamBankTest, Oob)
{
  std::vector<uint8_t> v;
  RamBank b({ 0, 1 }, v);
  EXPECT_THROW(b.getLocation(4), std::invalid_argument);
}
