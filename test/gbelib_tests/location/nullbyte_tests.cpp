#include "gtest/gtest.h"

#include "location/nulllocation.h"

using namespace std;

TEST(NullLocationTest, Read)
{
  NullLocation a;
  EXPECT_ANY_THROW(a.getWord());
}

TEST(NullLocationTest, Write)
{
  NullLocation a;
  EXPECT_ANY_THROW(a = uint8_t(0x3));
}
