#include "gtest/gtest.h"

#include "location/rambyte.h"


using namespace std;

TEST(RamLocationTest, testIndirect) {
  uint8_t buffer;
  auto a = RamByte(buffer);
  uint8_t value = 0x17;
  a << value;
  ASSERT_EQ(value, *a);
}

