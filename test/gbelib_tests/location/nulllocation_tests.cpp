#include "gtest/gtest.h"

#include "mem/rest/nulllocation.h"

TEST(NullLocationTest, Read)
{
  NullLocation a;
  EXPECT_ANY_THROW(a.get());
  EXPECT_ANY_THROW(a.get());
}

TEST(NullLocationTest, Write)
{
  NullLocation a;
  EXPECT_ANY_THROW(a.set(0x3));
  EXPECT_ANY_THROW(a.set(0x3));
}
