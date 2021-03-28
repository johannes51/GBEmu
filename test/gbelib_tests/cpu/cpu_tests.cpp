#include "gtest/gtest.h"

#include "cpu/cpu.h"
#include "cpu/cpuregisters.h"
#include "gb_factories/cartloader.h"
#include "gb_factories/memoryfactory.h"

#include <fstream>

using namespace std;
using namespace gb;

TEST(CpuTest, testConstruction)
{
  auto f = MemoryFactory(make_unique<CartLoader>("cpu_instrs.gb"));
  auto mem = f.constructMemoryLayout();
  auto reg = make_unique<CpuRegisters>();
  Cpu cpu(move(reg), mem);
}
