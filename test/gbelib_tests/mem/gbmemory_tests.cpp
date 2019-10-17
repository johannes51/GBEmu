#include "gtest/gtest.h"

#include "mem/gbmemory.h"
#include "util/location.h"


using namespace std;

TEST(GBMemoryTest, testGetByte) {
  auto a = GBMemory();
  ASSERT_EQ(0, **(a.getByte(0)));
}

TEST(GBMemoryTest, testGetWord) {
  auto a = GBMemory();
  ASSERT_EQ(0, **(a.getWord(0)));
}

