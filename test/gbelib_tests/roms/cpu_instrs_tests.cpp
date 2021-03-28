#include "gtest/gtest.h"

#include "cpu/cpu.h"
#include "cpu/cpuregisters.h"
#include "gb_factories/cartloader.h"
#include "gb_factories/memoryfactory.h"

#include <fstream>

using namespace std;
using namespace gb;

TEST(RomTest, testCpuInstructions)
{
  auto f = MemoryFactory(make_unique<CartLoader>("cpu_instrs.gb"));
  auto mem = f.constructMemoryLayout();
  auto reg = make_unique<CpuRegisters>();
  Cpu cpu(move(reg), mem);
  EXPECT_NO_THROW(cpu.clock()); // 0x0100 NOP
  EXPECT_NO_THROW(cpu.clock()); // 0x0101 JP 0x0637
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock()); // 0x0637 JP 0x0430
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  // EXPECT_NO_THROW(cpu.clock()); // 0x0430 DI
}
