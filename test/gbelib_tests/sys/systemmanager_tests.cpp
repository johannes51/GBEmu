#include "gtest/gtest.h"

#include <fstream>

#include "apu/apu.h"
#include "apu/gbmixer.h"
#include "cpu/cpu.h"
#include "cpu/cpuregisters.h"
#include "gb_factories/apufactory.h"
#include "gb_factories/apuregisterfactory.h"
#include "gb_factories/cartloader.h"
#include "gb_factories/instructionsetbuilder.h"
#include "gb_factories/memoryfactory.h"
#include "sys/systemmanager.h"

TEST(SystemManagerTest, Clock)
{
  gb::MemoryFactory m(std::make_unique<gb::CartLoader>("cpu_instrs.gb", "cpu_instrs.sav"));
  auto ml = m.constructMemoryLayout();
  std::vector<PeripheralSP> p {};
  ApuFactory c { ml };
  p.emplace_back(c.constructApu());
  SystemManager s(
      ml, std::make_unique<Cpu>(std::make_unique<CpuRegisters>(), ml, InstructionSetBuilder::construct()), p);
  EXPECT_NO_THROW(s.clock());
}
