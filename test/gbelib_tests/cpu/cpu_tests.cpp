#include "gtest/gtest.h"

#include "cpu/cpu.h"
#include "cpu/cpuregisters.h"
#include "gb_factories/cartloader.h"
#include "gb_factories/instructionsetbuilder.h"
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
  EXPECT_NO_THROW(Cpu cpu(move(reg), mem, InstructionDecoderUP {}));
}

TEST(CpuTest, Execution)
{
  auto f = MemoryFactory(make_unique<CartLoader>("cpu_instrs.gb"));
  auto mem = f.constructMemoryLayout();
  auto reg = make_unique<CpuRegisters>();
  auto* regAsPtr = reg.get();
  Cpu cpu(move(reg), mem, InstructionSetBuilder::construct());
  ASSERT_NO_THROW(cpu.clock()); // NOP
  EXPECT_EQ(0x0101, regAsPtr->get(WordRegisters::PC).get());
}

TEST(CpuTest, Execution2)
{
  auto f = MemoryFactory(make_unique<CartLoader>("cpu_instrs.gb"));
  auto mem = f.constructMemoryLayout();
  auto reg = make_unique<CpuRegisters>();
  auto* regAsPtr = reg.get();
  Cpu cpu(move(reg), mem, InstructionSetBuilder::construct());
  ASSERT_NO_THROW(cpu.clock()); // NOP
  EXPECT_EQ(0x0101, regAsPtr->get(WordRegisters::PC).get());
  EXPECT_NO_THROW(cpu.clock()); // 0x0101 JP 0x0637
  EXPECT_EQ(0x0104, regAsPtr->get(WordRegisters::PC).get());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_EQ(0x0637, regAsPtr->get(WordRegisters::PC).get());
}
