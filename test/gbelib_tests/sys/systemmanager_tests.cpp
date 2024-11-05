#include "gtest/gtest.h"

#include "mock/mockinterrupthandler.h"

#include "cpu/cpu.h"
#include "cpu/cpuregisters.h"
#include "gb_factories/apufactory.h"
#include "gb_factories/cartloader.h"
#include "gb_factories/gbfactory.h"
#include "gb_factories/instructionsetbuilder.h"
#include "gb_factories/memoryfactory.h"
#include "gb_factories/ppufactory.h"
#include "sys/systemmanager.h"

TEST(SystemManagerTest, Clock)
{
  GbFactory f {"cpu_instrs.gb", "cpu_instrs.sav"};
  const auto s = f.constructSystem();
  EXPECT_NO_THROW(s->clock());
  // std::vector<uint8_t> v;
  // gb::MemoryFactory m(std::make_unique<gb::CartLoader>("cpu_instrs.gb", "cpu_instrs.sav"), v);
  // auto ml = m.constructMemoryLayout();
  // std::vector<TickableSP> ps {};
  // ApuFactory c { ml };
  // ps.emplace_back(c.constructApu());
  // PpuFactory p { ml };
  // ps.emplace_back(p.constructPpu());
  // SystemManager s(std::make_unique<Cpu>(std::make_unique<CpuRegisters>(), ml, InstructionSetBuilder::construct(),
  //                     MockInterruptHandler::make()),
  //     ps, (IPixelBuffer*)nullptr);
}
