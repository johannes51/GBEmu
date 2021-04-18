#include "gtest/gtest.h"

#include <fstream>

#include "cpu/cpu.h"
#include "cpu/cpuregisters.h"
#include "gb_factories/cartloader.h"
#include "gb_factories/instructionsetbuilder.h"
#include "gb_factories/memoryfactory.h"
#include "sys/systemmanager.h"

TEST(SystemManagerTest, Clock)
{
  gb::MemoryFactory m(std::make_unique<gb::CartLoader>("cpu_instrs.gb", "cpu_instrs.sav"));
  SystemManager s(m.constructMemoryLayout(),
      std::make_unique<Cpu>(
          std::make_unique<CpuRegisters>(), m.constructMemoryLayout(), InstructionSetBuilder::construct()),
      std::vector<PeripheralSP> {});
  EXPECT_NO_THROW(s.clock());
}
