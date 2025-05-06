#include "gtest/gtest.h"

#include "gb_factories/gbfactory.h"

using namespace std;
using namespace gb;

TEST(RomTest, MemTiming)
{
  GbFactory g("mem_timing.gb", "mem_timing.sav");
  auto sm = g.constructSystem();

  for (size_t c = 0U; c < /*89670U*/ 29670U; ++c) { // TODO: way too slow after a point
    EXPECT_NO_THROW(sm->clock()) << "at count: " << c;
  }
}
