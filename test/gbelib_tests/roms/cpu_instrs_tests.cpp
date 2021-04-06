#include "gtest/gtest.h"

#include "cpu/cpu.h"
#include "cpu/cpuregisters.h"
#include "gb_factories/cartloader.h"
#include "gb_factories/instructionsetbuilder.h"
#include "gb_factories/memoryfactory.h"

#include <fstream>

using namespace std;
using namespace gb;

TEST(RomTest, CpuInstructions)
{
  Cpu cpu(make_unique<CpuRegisters>(),
      MemoryFactory { make_unique<CartLoader>("cpu_instrs.gb") }.constructMemoryLayout(),
      InstructionSetBuilder::construct());
  EXPECT_NO_THROW(cpu.clock()); // 0x0100 NOP
  EXPECT_NO_THROW(cpu.clock()); // 0x0101 JP 0x0637
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock()); // 0x0637 JP 0x0430
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock()); // 0x0430 DI
  EXPECT_NO_THROW(cpu.clock()); // 0x0431 LD SP, 0xDFFF
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock()); // 0x0434 LD (0xD600), A
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock()); // 0x0437 LD A, 0x00
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock()); // 0x0439 LDH (0x07), A
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
}
