#include "gtest/gtest.h"

#include "cpu/cpu.h"
#include "cpu/cpuregisters.h"
#include "gb_factories/cartloader.h"
#include "gb_factories/instructionsetbuilder.h"
#include "gb_factories/memoryfactory.h"

#include <fstream>

using namespace std;
using namespace gb;

TEST(RomTest, InstructionTiming)
{
  Cpu cpu(make_unique<CpuRegisters>(),
      MemoryFactory { make_unique<CartLoader>("instr_timing.gb") }.constructMemoryLayout(),
      InstructionSetBuilder::construct());
  EXPECT_NO_THROW(cpu.clock()); // 0x0100 NOP
  EXPECT_NO_THROW(cpu.clock()); // 0x0101 JP 0x0213
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock()); // 0x0213 LD HL, 0x4000
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock()); // 0x0216 JP 0x0200
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock()); // 0x0200 LD B, A
  EXPECT_NO_THROW(cpu.clock()); // 0x0201 LD DE, 0xC000
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock()); // 0x0204 LD C, 0x10
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock()); // 0x0206 LD A, (HL+)
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock()); // 0x0207 LD (DE), A
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock()); // 0x0208 INC E
  EXPECT_NO_THROW(cpu.clock()); // 0x0208 JR NZ, 0xFB
  EXPECT_NO_THROW(cpu.clock());
}
