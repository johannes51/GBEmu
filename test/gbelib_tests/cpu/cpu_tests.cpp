#include "gtest/gtest.h"

#include "cpu/cpu.h"
#include "cpu/cpuregisters.h"
#include "gb_factories/cartloader.h"
#include "gb_factories/memoryfactory.h"

#include <fstream>

using namespace std;
using namespace gb;

TEST(CpuTest, testClock) {
  auto f = MemoryFactory(make_unique<CartLoader>("Tetris.gb", "Tetris.sav"));
  auto mem = f.constructMemoryLayout();
  auto reg = make_unique<CpuRegisters>();
  Cpu cpu(move(reg), mem);
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_ANY_THROW(cpu.clock());
}
