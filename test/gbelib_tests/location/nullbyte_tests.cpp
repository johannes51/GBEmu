#include "gtest/gtest.h"

#include "location/nullbyte.h"

using namespace std;

TEST(NullByteTest, Read)
{
  NullByte a;
  EXPECT_ANY_THROW(a.get());
}

TEST(NullByteTest, Write)
{
  NullByte a;
  EXPECT_ANY_THROW(a.set(0x3));
}
