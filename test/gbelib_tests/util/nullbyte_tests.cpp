#include "gtest/gtest.h"

#include "util/nullbyte.h"


using namespace std;

TEST(NullByteTest, testIndirect) {
  auto a = NullByte();
  ASSERT_ANY_THROW(*a);
}

