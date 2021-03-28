#include "gtest/gtest.h"

#include "location/nullbyte.h"


using namespace std;

TEST(NullByteTest, testRead) {
  auto a = NullByte();
  ASSERT_ANY_THROW(*a);
}

TEST(NullByteTest, testWrite) {
  auto a = NullByte();
  ASSERT_ANY_THROW(a << 0x3);
}

