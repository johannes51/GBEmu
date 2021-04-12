#include "gtest/gtest.h"

#include "cpu/cpu.h"
#include "cpu/cpuregisters.h"
#include "gb_factories/cartloader.h"
#include "gb_factories/instructionsetbuilder.h"
#include "gb_factories/memoryfactory.h"

#include <fstream>

using namespace std;
using namespace gb;

TEST(RomTest, InteruptTime)
{
  Cpu cpu(make_unique<CpuRegisters>(),
      MemoryFactory { make_unique<CartLoader>("interrupt_time.gb") }.constructMemoryLayout(),
      InstructionSetBuilder::construct());
  for (int var = 0; var < 117464; ++var) {
    EXPECT_NO_THROW(cpu.clock()) << var;
  }
  EXPECT_NO_THROW(cpu.clock()); // 0xC2C1 CB SRL B
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock()); // 0xC2C3 CB RR C
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock()); // 0xC2C5 CB RR D
  EXPECT_NO_THROW(cpu.clock());
  //  EXPECT_NO_THROW(cpu.clock()); // 0xC2C7 RRA
}
