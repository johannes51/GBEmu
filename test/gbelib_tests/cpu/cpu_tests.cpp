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
  std::vector<uint8_t> v;
  auto f = MemoryFactory(make_unique<CartLoader>("cpu_instrs.gb"), v);
  auto mem = f.constructMemoryLayout();
  auto reg = make_unique<CpuRegisters>();
  EXPECT_NO_THROW(Cpu cpu(std::move(reg), mem, InstructionDecoderUP {}));
}

TEST(CpuTest, Execution)
{
  std::vector<uint8_t> v;
  auto f = MemoryFactory(make_unique<CartLoader>("cpu_instrs.gb"), v);
  auto mem = f.constructMemoryLayout();
  auto reg = make_unique<CpuRegisters>();
  auto* regAsPtr = reg.get();
  Cpu cpu(std::move(reg), mem, InstructionSetBuilder::construct());
  ASSERT_NO_THROW(cpu.clock()); // NOP
  EXPECT_EQ(0x0101, regAsPtr->get(WordRegister::PC)->getWord());
}

TEST(CpuTest, Execution2)
{
  std::vector<uint8_t> v;
  auto f = MemoryFactory(make_unique<CartLoader>("cpu_instrs.gb"), v);
  auto mem = f.constructMemoryLayout();
  auto reg = make_unique<CpuRegisters>();
  auto* regAsPtr = reg.get();
  Cpu cpu(std::move(reg), mem, InstructionSetBuilder::construct());
  ASSERT_NO_THROW(cpu.clock()); // NOP
  EXPECT_EQ(0x0101, regAsPtr->get(WordRegister::PC)->getWord());
  EXPECT_NO_THROW(cpu.clock()); // 0x0101 JP 0x0637
  EXPECT_EQ(0x0104, regAsPtr->get(WordRegister::PC)->getWord());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_EQ(0x0637, regAsPtr->get(WordRegister::PC)->getWord());
}
