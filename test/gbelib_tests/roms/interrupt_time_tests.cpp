#include "gtest/gtest.h"

#include "gb_factories/gbfactory.h"

using namespace std;
using namespace gb;

TEST(RomTest, InteruptTime)
{
  GbFactory g("interrupt_time.gb", "interrupt_time.sav");
  auto sm = g.constructSystem();

  for (int var = 0; var < 66693; ++var) {
    EXPECT_NO_THROW(sm->clock()) << var; // TODO: wartet auf irgendwas
  }

  //-----------------------------------------------DONE-----------------------------------------------------------------
}
