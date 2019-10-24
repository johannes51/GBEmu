#include "gtest/gtest.h"

#include "mem/rambank.h"
#include "location/location.h"

TEST(RomBankTest, testIndirect) {
  RamBank b({0, 16});
  auto writeByte = b.getByte(4);
  uint8_t value = 0xA2;
  writeByte->set(value);
  auto readByte = b.getByte(4);
  EXPECT_EQ(value, readByte->get());
}

