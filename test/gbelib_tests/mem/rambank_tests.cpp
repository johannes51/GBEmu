#include "gtest/gtest.h"

#include "mem/rambank.h"
#include "location/location.h"


using namespace std;

TEST(RamBankTest, testIndirect) {
  RamBank b({0, 16});
  auto writeByte = b.getByte(4);
  uint8_t value = 0xA2;
  *writeByte << value;
  auto readByte = b.getByte(4);
  ASSERT_EQ(value, **readByte);
}

