#include "gtest/gtest.h"

#include "gb_factories/gbfactory.h"

using namespace std;
using namespace gb;

TEST(RomTest, CpuInstructions)
{
  GbFactory g("cpu_instrs.gb", "cpu_instrs.sav");
  auto sm = g.constructSystem();

  for (size_t c = 0U; c < 30000U; ++c) { // TODO: way too slow after a point
    EXPECT_NO_THROW(sm->clock()) << "at count: " << c;
  }
}
