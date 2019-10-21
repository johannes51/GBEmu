#include "gtest/gtest.h"

#include "mem/nullbank.h"
#include "location/location.h"


using namespace std;

TEST(NullBankTest, testWrite) {
  NullBank b{{0, 16}};
  auto writeByte = b.getByte(3);
  uint8_t value = 0xA2;
  *writeByte << value;
  auto readByte = b.getByte(3);
  ASSERT_EQ(0, **readByte);
}

