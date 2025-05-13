#include "gtest/gtest.h"

#include "gb_factories/gbfactory.h"

using namespace std;
using namespace gb;

TEST(RomTest, InteruptTime)
{
  GbFactory g("interrupt_time.gb", "interrupt_time.sav");
  auto sm = g.constructSystem();

  for (size_t c = 0U; c < 53470U; ++c) {
    EXPECT_NO_THROW(sm->clock()) << "at count: " << c;
  }
  EXPECT_ANY_THROW(sm->clock()); // TODO: write on ROM
}
