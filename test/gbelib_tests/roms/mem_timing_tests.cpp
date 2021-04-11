#include "gtest/gtest.h"

#include "cpu/cpu.h"
#include "cpu/cpuregisters.h"
#include "gb_factories/cartloader.h"
#include "gb_factories/instructionsetbuilder.h"
#include "gb_factories/memoryfactory.h"

#include <fstream>

using namespace std;
using namespace gb;

TEST(RomTest, MemTiming)
{
  Cpu cpu(make_unique<CpuRegisters>(),
      MemoryFactory { make_unique<CartLoader>("mem_timing.gb") }.constructMemoryLayout(),
      InstructionSetBuilder::construct());
  EXPECT_NO_THROW(cpu.clock()); // 0x0100 NOP
  EXPECT_NO_THROW(cpu.clock()); // 0x0101 JP 0x0213
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  for (int var = 0; var < 63934; ++var) {
    EXPECT_NO_THROW(cpu.clock()) << var;
  }
  EXPECT_NO_THROW(cpu.clock()); // 0x085B SUB 0x88
  EXPECT_NO_THROW(cpu.clock());
  for (int var = 0; var < 79; ++var) {
    EXPECT_NO_THROW(cpu.clock()) << var;
  }
  EXPECT_NO_THROW(cpu.clock()); // 0x0271 LD B, (HL)
  EXPECT_NO_THROW(cpu.clock());
  for (int var = 0; var < 8; ++var) {
    EXPECT_NO_THROW(cpu.clock()) << var;
  }
  EXPECT_NO_THROW(cpu.clock()); // 0x0278 LD H, 0x08
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock()); // 0x027A CB SRL B
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock()); // 0x027C CB RR C
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock()); // 0x027E CB RR D
  EXPECT_NO_THROW(cpu.clock());
  //  EXPECT_NO_THROW(cpu.clock()); // 0x0280 RRA
}
