#include "gtest/gtest.h"

#include "gb_factories/gbfactory.h"

using namespace std;
using namespace gb;

TEST(RomTest, MemTiming2)
{
  GbFactory g("mem_timing2.gb", "mem_timing2.sav");
  auto sm = g.constructSystem();

  for (size_t c = 0U; c < 12419U; ++c) {
    EXPECT_NO_THROW(sm->clock()) << "at count: " << c;
  }
  // EXPECT_NO_THROW(sm->clock()); // TODO: write on ROM
}
