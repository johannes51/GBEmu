#include "gtest/gtest.h"

#include "mock/mockinterrupthandler.h"

#include "cpu/cpu.h"
#include "cpu/cpuregisters.h"
#include "gb_factories/cartloader.h"
#include "gb_factories/instructionsetbuilder.h"
#include "gb_factories/memoryfactory.h"

using namespace std;
using namespace gb;

TEST(CpuTest, Construction)
{
  std::vector<uint8_t> v;
  auto f = MemoryFactory(make_unique<CartLoader>("cpu_instrs.gb", "cpu_instrs.sav"), v);
  auto mem = f.constructMemoryLayout();
  auto reg = make_unique<CpuRegisters>();
  EXPECT_NO_THROW(Cpu cpu(std::move(reg), mem, InstructionDecoderUP {}, InterruptHandlerUP {}));
}

TEST(CpuTest, Execution)
{
  std::vector<uint8_t> v;
  auto f = MemoryFactory(make_unique<CartLoader>("cpu_instrs.gb", "cpu_instrs.sav"), v);
  auto mem = f.constructMemoryLayout();
  auto reg = make_unique<CpuRegisters>();
  auto* regAsPtr = reg.get();
  Cpu cpu(std::move(reg), mem, InstructionSetBuilder::construct(), MockInterruptHandler::make());
  ASSERT_NO_THROW(cpu.clock()); // NOP
  EXPECT_EQ(0x0101U, regAsPtr->get(WordRegister::PC)->getWord());
}

TEST(CpuTest, Execution2)
{
  std::vector<uint8_t> v;
  auto f = MemoryFactory(make_unique<CartLoader>("cpu_instrs.gb", "cpu_instrs.sav"), v);
  auto mem = f.constructMemoryLayout();
  auto reg = make_unique<CpuRegisters>();
  auto* regAsPtr = reg.get();
  Cpu cpu(std::move(reg), mem, InstructionSetBuilder::construct(), MockInterruptHandler::make());
  ASSERT_NO_THROW(cpu.clock()); // NOP
  EXPECT_EQ(0x0101U, regAsPtr->get(WordRegister::PC)->getWord());
  EXPECT_NO_THROW(cpu.clock()); // 0x0101 JP 0x0637
  EXPECT_EQ(0x0104U, regAsPtr->get(WordRegister::PC)->getWord());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_EQ(0x0637U, regAsPtr->get(WordRegister::PC)->getWord());
}

TEST(CpuTest, Interrupt)
{
  std::vector<uint8_t> v;
  auto f = MemoryFactory(make_unique<CartLoader>("cpu_instrs.gb", "cpu_instrs.sav"), v);
  auto mem = f.constructMemoryLayout();
  auto reg = make_unique<CpuRegisters>();
  auto* regAsPtr = reg.get();
  MockInterruptHandler* ih = nullptr;
  Cpu cpu(std::move(reg), mem, InstructionSetBuilder::construct(), MockInterruptHandler::make(ih, true, 0x0100U));

  regAsPtr->getFlags().disableInterrupt();
  ASSERT_NO_THROW(cpu.clock()); // NOP
  EXPECT_EQ(0x0101U, regAsPtr->get(WordRegister::PC)->getWord());
  regAsPtr->getFlags().enableInterrupt();
  ASSERT_NO_THROW(cpu.clock()); // I1
  EXPECT_FALSE(ih->wasExecuted());
  EXPECT_EQ(0x0101U, regAsPtr->get(WordRegister::PC)->getWord());
  ASSERT_NO_THROW(cpu.clock()); // I2
  EXPECT_FALSE(ih->wasExecuted());
  EXPECT_EQ(0x0101U, regAsPtr->get(WordRegister::PC)->getWord());
  ASSERT_NO_THROW(cpu.clock()); // I3
  EXPECT_FALSE(ih->wasExecuted());
  EXPECT_EQ(0x0101U, regAsPtr->get(WordRegister::PC)->getWord());
  ASSERT_NO_THROW(cpu.clock()); // I4
  EXPECT_FALSE(ih->wasExecuted());
  EXPECT_EQ(0x0101U, regAsPtr->get(WordRegister::PC)->getWord());
  ASSERT_NO_THROW(cpu.clock()); // I5
  EXPECT_TRUE(ih->wasExecuted());
  EXPECT_EQ(0x0100U, regAsPtr->get(WordRegister::PC)->getWord());
}
