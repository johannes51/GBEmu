#include "gtest/gtest.h"

#include "location/location8.h"
#include "mem/rambank.h"

using namespace std;

TEST(RamBankTest, Write8)
{
  std::vector<uint8_t> v { 16U };
  RamBank b({ 0, 16 }, v);
  auto writeByte = b.getLocation8(4);
  uint8_t value = 0xA2;
  *writeByte = value;
  auto readByte = b.getLocation8(4)->get();
  EXPECT_EQ(value, readByte);
}

TEST(RamBankTest, Write16)
{
  std::vector<uint8_t> v(16U);
  RamBank b({ 0, 16 }, v);
  auto writeWord = b.getLocation16(4);
  uint16_t value = 0xA27E;
  *writeWord = value;
  auto readWord = b.getLocation16(4)->get();
  EXPECT_EQ(value, readWord);
}

TEST(RamBankTest, Oob)
{
  std::vector<uint8_t> v;
  RamBank b({ 0, 1 }, v);
  EXPECT_THROW(b.getLocation8(4), std::invalid_argument);
}

TEST(RamBankTest, WordOob)
{
  std::vector<uint8_t> v;
  RamBank b({ 0, 1 }, v);
  EXPECT_THROW(b.getLocation16(1), std::invalid_argument);
}
