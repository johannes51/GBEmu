#include "gtest/gtest.h"

#include "mem/ramlocation.h"


using namespace std;

TEST(RamLocationTest, testIndirect) {
  auto a = RamLocation(0);
  ASSERT_EQ(0, *a);
}

