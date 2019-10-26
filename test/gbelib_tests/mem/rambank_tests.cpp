#include "gtest/gtest.h"

#include "location/location.h"
#include "mem/rambank.h"

using namespace std;

TEST(RamBankTest, testIndirect)
{
  RamBank b({ 0, 16 });
  auto writeByte = b.getByte(4);
  uint8_t value = 0xA2;
  writeByte.set(value);
  auto readByte = b.getByte(4);
  EXPECT_EQ(value, readByte.get());
}
