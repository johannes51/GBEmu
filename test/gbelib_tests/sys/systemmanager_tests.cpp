#include "gtest/gtest.h"

#include <fstream>

#include "apu/apu.h"
#include "cpu/cpu.h"
#include "cpu/cpuregisters.h"
#include "gb_factories/cartloader.h"
#include "gb_factories/channelfactory.h"
#include "gb_factories/instructionsetbuilder.h"
#include "gb_factories/memoryfactory.h"
#include "sys/systemmanager.h"

TEST(SystemManagerTest, Clock)
{
  gb::MemoryFactory m(std::make_unique<gb::CartLoader>("cpu_instrs.gb", "cpu_instrs.sav"));
  auto ml = m.constructMemoryLayout();
  std::vector<PeripheralSP> p {};
  ChannelFactory c { ml };
  p.emplace_back(std::make_shared<Apu>(c.constructChannels(), nullptr));
  SystemManager s(
      ml, std::make_unique<Cpu>(std::make_unique<CpuRegisters>(), ml, InstructionSetBuilder::construct()), p);
  EXPECT_NO_THROW(s.clock());
}
