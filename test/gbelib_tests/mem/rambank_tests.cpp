#include "gtest/gtest.h"

#include "location/location.h"
#include "mem/rambank.h"

using namespace std;

TEST(RamBankTest, testWrite8)
{
  RamBank b({ 0, 16 });
  auto writeByte = b.getByte(4);
  uint8_t value = 0xA2;
  writeByte.set(value);
  auto readByte = b.getByte(4);
  EXPECT_EQ(value, readByte.get());
}

TEST(RamBankTest, testWrite16)
{
  RamBank b({ 0, 1 });
  auto writeByte = b.getWord(0);
  uint16_t value = 0xA27E;
  writeByte.set(value);
  auto readByte = b.getWord(0);
  EXPECT_EQ(value, readByte.get());
}

TEST(RamBankTest, testOob)
{
  RamBank b({ 0, 1 });
  EXPECT_THROW(b.getByte(4), std::invalid_argument);
}
