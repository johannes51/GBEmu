#include "gtest/gtest.h"

#include "cpu/cpu.h"
#include "cpu/cpuregisters.h"
#include "gb_factories/cartloader.h"
#include "gb_factories/memoryfactory.h"

#include <fstream>

using namespace std;
using namespace gb;

TEST(CpuTest, testTetris)
{
  auto f = MemoryFactory(make_unique<CartLoader>("Tetris.gb"));
  auto mem = f.constructMemoryLayout();
  auto reg = make_unique<CpuRegisters>();
  Cpu cpu(move(reg), mem);
  EXPECT_NO_THROW(cpu.clock()); // 0x0100 NOP
  EXPECT_NO_THROW(cpu.clock()); // 0x0101 JP 0x0150
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock()); // 0x0150 JP 0x020C
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock()); // 0x020C XOR A
  EXPECT_NO_THROW(cpu.clock()); // 0x020D LD HL, 0xDFFF
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock()); // 0x0210 LD C, 0x10
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock()); // 0x0212 LD H, B
  EXPECT_NO_THROW(cpu.clock()); // 0x0213 NOP
  EXPECT_NO_THROW(cpu.clock()); // 0x0214 LD (HL-),A
  EXPECT_NO_THROW(cpu.clock());
  EXPECT_NO_THROW(cpu.clock()); // 0x0215 DEC B
}

TEST(CpuTest, testLoads)
{
  auto f = MemoryFactory(make_unique<CartLoader>("loads.gb"));
  auto mem = f.constructMemoryLayout();
  auto reg = make_unique<CpuRegisters>();
  Cpu cpu(move(reg), mem);
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
  EXPECT_ANY_THROW(cpu.clock()); // 0x0208 INC E
}
