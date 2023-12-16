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
  for (int c2 = 0; c2 < 15; ++c2) {
    for (int counter = 0; counter < 255; ++counter) {
      EXPECT_NO_THROW(cpu.clock()); // 0x0206 LD A, (HL+)
      EXPECT_NO_THROW(cpu.clock());
      EXPECT_NO_THROW(cpu.clock()); // 0x0207 LD (DE), A
      EXPECT_NO_THROW(cpu.clock());
      EXPECT_NO_THROW(cpu.clock()); // 0x0208 INC E
      EXPECT_NO_THROW(cpu.clock()); // 0x0209 JR NZ, 0xFB (-5, 0x0206)
      EXPECT_NO_THROW(cpu.clock());
      EXPECT_NO_THROW(cpu.clock());
    }
    EXPECT_NO_THROW(cpu.clock()); // 0x0206 LD A, (HL+)
    EXPECT_NO_THROW(cpu.clock());
    EXPECT_NO_THROW(cpu.clock()); // 0x0207 LD (DE), A
    EXPECT_NO_THROW(cpu.clock());
    EXPECT_NO_THROW(cpu.clock()); // 0x0208 INC E
    EXPECT_NO_THROW(cpu.clock()); // 0x0209 JR NZ, 0xFB (-5, 0x0206)
    EXPECT_NO_THROW(cpu.clock());
    EXPECT_NO_THROW(cpu.clock()); // 0x020B INC D
    EXPECT_NO_THROW(cpu.clock()); // 0x020C DEC C
    EXPECT_NO_THROW(cpu.clock()); // 0x020D JR NZ, 0xF7 (-9, 0x0206)
    EXPECT_NO_THROW(cpu.clock());
    EXPECT_NO_THROW(cpu.clock());
  }
  for (int counter = 0; counter < 255; ++counter) {
    EXPECT_NO_THROW(cpu.clock()); // 0x0206 LD A, (HL+)
    EXPECT_NO_THROW(cpu.clock());
    EXPECT_NO_THROW(cpu.clock()); // 0x0207 LD (DE), A
    EXPECT_NO_THROW(cpu.clock());
    EXPECT_NO_THROW(cpu.clock()); // 0x0208 INC E
    EXPECT_NO_THROW(cpu.clock()); // 0x0209 JR NZ, 0xFB (-5, 0x0206)
    EXPECT_NO_THROW(cpu.clock());
    EXPECT_NO_THROW(cpu.clock());
  }
  EXPECT_NO_THROW(cpu.clock()); // 0x0206 LD A, (HL+)
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock()); // 0x0207 LD (DE), A
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock()); // 0x0208 INC E
  EXPECT_NO_THROW(cpu.clock()); // 0x0209 JR NZ, 0xFB (-5, 0x0206)
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock()); // 0x020B INC D
  EXPECT_NO_THROW(cpu.clock()); // 0x020C DEC C
  EXPECT_NO_THROW(cpu.clock()); // 0x020D JR NZ, 0xF7 (-9, 0x0206)
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock()); // 0x020F LD A, B
  EXPECT_NO_THROW(cpu.clock()); // 0x0210 JP 0xC000
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock()); // 0xC000 JP 0xC220
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock()); // 0xC220 DI
  EXPECT_NO_THROW(cpu.clock()); // 0xC221 LD SP, 0xDFFF
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock()); // 0xC224 LD (0xD800), A
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock()); // 0xC227 LD A, 0x00
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock()); // 0xC229 LDH (0x07), A
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  for (int var = 0; var < 17704; ++var) {
    EXPECT_NO_THROW(cpu.clock()) << var;
  }
  EXPECT_NO_THROW(cpu.clock()); // 0xC44F AND 0x10
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock()); // 0xC451 CALL NZ, 0xC48B
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock()); // 0xC454 LD A, 0x20
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock()); // 0xC456 CALL 0xC47D
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock()); // 0xC47D LD HL, 0x9800
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock()); // 0xC480 LD B, 0x04
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock()); // 0xC482 LD (HL), A
  EXPECT_NO_THROW(cpu.clock()); // FIXME: writes to VRAM, make that work

  //-----------------------------------------------DONE-----------------------------------------------------------------
}
