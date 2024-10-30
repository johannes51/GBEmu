#include "gtest/gtest.h"

#include "gb_factories/gbfactory.h"

using namespace std;
using namespace gb;

TEST(RomTest, MemTiming2)
{
  GbFactory g("mem_timing2.gb", "mem_timing2.sav");
  auto sm = g.constructSystem();

  for (int var = 0; var < 12419; ++var) {
    EXPECT_NO_THROW(sm->clock()) << var;
  }
  EXPECT_ANY_THROW(sm->clock()); // TODO: write on rom wieso?

  //-----------------------------------------------DONE-----------------------------------------------------------------
}
