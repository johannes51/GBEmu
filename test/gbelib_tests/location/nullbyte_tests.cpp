#include "gtest/gtest.h"

#include "location/nullbyte.h"


using namespace std;

TEST(NullByteTest, testRead) {
  NullByte a;
  ASSERT_ANY_THROW(a.get());
}

TEST(NullByteTest, testWrite) {
  NullByte a;
  ASSERT_ANY_THROW(a.set(0x3));
}

