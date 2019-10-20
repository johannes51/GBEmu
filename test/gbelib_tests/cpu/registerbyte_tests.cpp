#include "gtest/gtest.h"

#include "location/registerbyte.h"


using namespace std;

TEST(RegisterByteTest, testByte) {
  uint8_t buffer = 0x4E;
  auto byte = RegisterByte(buffer);
  ASSERT_EQ(0x4E, *byte);
}


