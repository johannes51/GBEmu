#include "gtest/gtest.h"

#include "location/nulllocation.h"

TEST(NullLocationTest, Read)
{
  NullLocation a;
  EXPECT_ANY_THROW(a.getByte());
  EXPECT_ANY_THROW(a.getWord());
}

TEST(NullLocationTest, Write)
{
  NullLocation a;
  EXPECT_ANY_THROW(a = uint8_t(0x3));
  EXPECT_ANY_THROW(a = uint16_t(0x3));
}
