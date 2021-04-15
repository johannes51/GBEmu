#include "gtest/gtest.h"

#include "cpu/cpu.h"
#include "cpu/cpuregisters.h"
#include "gb_factories/cartloader.h"
#include "gb_factories/instructionsetbuilder.h"
#include "gb_factories/memoryfactory.h"

#include <fstream>

using namespace std;
using namespace gb;

TEST(RomTest, MemTiming2)
{
  Cpu cpu(make_unique<CpuRegisters>(),
      MemoryFactory { make_unique<CartLoader>("mem_timing2.gb") }.constructMemoryLayout(),
      InstructionSetBuilder::construct());
  for (int var = 0; var < 76414; ++var) {
    EXPECT_NO_THROW(cpu.clock()) << var;
  }
  EXPECT_NO_THROW(cpu.clock()); // 0x24D1 CB SRL B
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock()); // 0x24D3 CB RR C
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock()); // 0x24D5 CB RR D
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock()); // 0x24D7 RRCA
  for (int var = 0; var < 5110; ++var) {
    EXPECT_NO_THROW(cpu.clock()) << var;
  }
  EXPECT_NO_THROW(cpu.clock()); // 0x2519 JP (HL)
  for (int var = 0; var < 37996; ++var) {
    EXPECT_NO_THROW(cpu.clock()) << var;
  }
  EXPECT_NO_THROW(cpu.clock()); // 0x231F CB SRL A
  EXPECT_NO_THROW(cpu.clock());
  for (int var = 0; var < 12; ++var) {
    EXPECT_NO_THROW(cpu.clock()) << var;
  }
  EXPECT_NO_THROW(cpu.clock()); // 0x2329 CB SWAP A
  EXPECT_NO_THROW(cpu.clock());
  for (int var = 0; var < 15; ++var) {
    EXPECT_NO_THROW(cpu.clock()) << var;
  }
  EXPECT_NO_THROW(cpu.clock()); // 0x2344 CALL 0x250D
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());

  //-----------------------------------------------DONE-----------------------------------------------------------------
}
