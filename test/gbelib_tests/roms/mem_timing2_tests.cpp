#include "gtest/gtest.h"

#include "cpu/cpu.h"
#include "cpu/cpuregisters.h"
#include "gb_factories/cartloader.h"
#include "gb_factories/instructionsetbuilder.h"
#include "gb_factories/memoryfactory.h"

using namespace std;
using namespace gb;

TEST(RomTest, MemTiming2)
{
  std::vector<uint8_t> v;
  Cpu cpu(make_unique<CpuRegisters>(),
      MemoryFactory { make_unique<CartLoader>("mem_timing2.gb"), v }.constructMemoryLayout(),
      InstructionSetBuilder::construct());

  for (int var = 0; var < 12420; ++var) {
    EXPECT_NO_THROW(cpu.clock()) << var;
  }
  EXPECT_ANY_THROW(cpu.clock()); // TODO: write on rom wieso?

  //-----------------------------------------------DONE-----------------------------------------------------------------
}
