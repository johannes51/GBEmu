#include "gtest/gtest.h"

#include "cpu/cpu.h"
#include "cpu/cpuregisters.h"
#include "gb_factories/cartloader.h"
#include "gb_factories/instructionsetbuilder.h"
#include "gb_factories/memoryfactory.h"

using namespace std;
using namespace gb;

TEST(RomTest, InteruptTime)
{
  std::vector<uint8_t> v;
  Cpu cpu(make_unique<CpuRegisters>(),
      MemoryFactory { make_unique<CartLoader>("interrupt_time.gb"), v }.constructMemoryLayout(),
      InstructionSetBuilder::construct());

  for (int var = 0; var < 66693; ++var) {
    EXPECT_NO_THROW(cpu.clock()) << var; // TODO: wartet auf irgendwas
  }

  //-----------------------------------------------DONE-----------------------------------------------------------------
}
