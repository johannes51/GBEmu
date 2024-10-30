#include "gtest/gtest.h"

#include "gb_factories/gbfactory.h"

using namespace std;
using namespace gb;

TEST(RomTest, MemTiming)
{
  GbFactory g("mem_timing.gb", "mem_timing.sav");
  auto sm = g.constructSystem();

  EXPECT_NO_THROW(sm->clock()); // 0x0100 NOP
  EXPECT_NO_THROW(sm->clock()); // 0x0101 JP 0x0213
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  for (int var = 0; var < 17735; ++var) {
    EXPECT_NO_THROW(sm->clock()) << var;
  }
  EXPECT_ANY_THROW(sm->clock()); // TODO: unable to provide register wieso?

  //-----------------------------------------------DONE-----------------------------------------------------------------
}
