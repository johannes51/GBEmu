#include "gtest/gtest.h"

#include "gb_factories/gbfactory.h"

using namespace std;

TEST(RomTest, InstructionTiming)
{
  GbFactory g("instr_timing.gb", "instr_timing.sav");
  auto sm = g.constructSystem();

  for (size_t c = 0U; c < 48986U; ++c) {
    EXPECT_NO_THROW(sm->clock()) << "at count: " << c;
  }
  // EXPECT_NO_THROW(sm->clock()); // TODO: Unimplmented opcode
}
