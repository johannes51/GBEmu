#include "gtest/gtest.h"

#include <fstream>

#include "cpu/cpu.h"
#include "gb_factories/memoryfactory.h"
#include "gb_factories/cartloader.h"
#include "cpu/cpuregisters.h"


using namespace std;
using namespace gb;

TEST(CpuTest, testClock) {
  auto f = MemoryFactory(std::make_unique<CartLoader>(std::ifstream{"Tetris.gb", std::ios_base::binary | std::ios_base::in},
                                                      std::fstream{"Tetris.sav", std::ios_base::binary | std::ios_base::in}
                           ));
  auto mem = f.constructMemoryLayout();
  auto reg = std::make_unique<CpuRegisters>();
  Cpu cpu(std::move(reg), mem);
  ASSERT_NO_THROW(cpu.clock());
}


