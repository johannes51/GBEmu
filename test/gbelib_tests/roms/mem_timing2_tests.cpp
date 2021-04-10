#include "gtest/gtest.h"

#include "cpu/cpu.h"
#include "cpu/cpuregisters.h"
#include "gb_factories/cartloader.h"
#include "gb_factories/instructionsetbuilder.h"
#include "gb_factories/memoryfactory.h"

#include <fstream>

using namespace std;
using namespace gb;

TEST(RomTest, MemTiming2)
{
  Cpu cpu(make_unique<CpuRegisters>(),
      MemoryFactory { make_unique<CartLoader>("mem_timing2.gb") }.constructMemoryLayout(),
      InstructionSetBuilder::construct());
  for (int var = 0; var < 76414; ++var) {
    EXPECT_NO_THROW(cpu.clock()) << var;
  }
  //  EXPECT_NO_THROW(cpu.clock()); // 0x24D1 TODO: CB prefix unimplemented
}
