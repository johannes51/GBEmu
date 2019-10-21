#include "gtest/gtest.h"

#include "location/nullbyte.h"


using namespace std;

TEST(NullByteTest, testRead) {
  NullByte a;
  ASSERT_ANY_THROW(*a);
}

TEST(NullByteTest, testWrite) {
  NullByte a;
  ASSERT_ANY_THROW(a << 0x3);
}

