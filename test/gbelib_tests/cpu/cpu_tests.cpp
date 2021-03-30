#include "gtest/gtest.h"

#include "cpu/cpu.h"
#include "cpu/cpuregisters.h"
#include "gb_factories/cartloader.h"
#include "gb_factories/memoryfactory.h"
#include "location/location.h"

#include <fstream>

using namespace std;
using namespace gb;

TEST(CpuTest, Construction)
{
  auto f = MemoryFactory(make_unique<CartLoader>("cpu_instrs.gb"));
  auto mem = f.constructMemoryLayout();
  auto reg = make_unique<CpuRegisters>();
  EXPECT_NO_THROW(Cpu cpu(move(reg), mem));
}

TEST(CpuTest, Execution)
{
  auto f = MemoryFactory(make_unique<CartLoader>("cpu_instrs.gb"));
  auto mem = f.constructMemoryLayout();
  auto reg = make_unique<CpuRegisters>();
  auto regAsPtr = reg.get();
  Cpu cpu(move(reg), mem);
  ASSERT_NO_THROW(cpu.clock()); // NOP
  ASSERT_NO_THROW(cpu.clock()); // JP
  ASSERT_NO_THROW(cpu.clock()); // JP
  ASSERT_NO_THROW(cpu.clock()); // JP
  ASSERT_NO_THROW(cpu.clock()); // JP
  EXPECT_EQ(0x0637, regAsPtr->get(WordRegisters::PC).get());
}
