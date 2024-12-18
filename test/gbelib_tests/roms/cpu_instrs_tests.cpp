#include "gtest/gtest.h"

#include "gb_factories/gbfactory.h"

using namespace std;
using namespace gb;

TEST(RomTest, CpuInstructions)
{
  GbFactory g("cpu_instrs.gb", "cpu_instrs.sav");
  auto sm = g.constructSystem();

  EXPECT_NO_THROW(sm->clock()); // 0x0100 NOP
  EXPECT_NO_THROW(sm->clock()); // 0x0101 JP 0x0637
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock()); // 0x0637 JP 0x0430
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock()); // 0x0430 DI
  EXPECT_NO_THROW(sm->clock()); // 0x0431 LD SP, 0xDFFF
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock()); // 0x0434 LD (0xD600), A
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock()); // 0x0437 LD A, 0x00
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock()); // 0x0439 LDH (0x07), A
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock()); // 0x043B LD A, 0x00
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock()); // 0x043D LD C, 0x0F
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock()); // 0x043F LD A, 0x00
  EXPECT_NO_THROW(sm->clock());

  EXPECT_NO_THROW(sm->clock()); // 0x0441 LDH (0xFF), A
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock()); // 0x0443 LD A, 0x00
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock()); // 0x0445 LD (0x26), A
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock()); // 0x0447 LD A, 0x80
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock()); // 0x0449 LDH (0x26), A
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock()); // 0x044B LD A, 0xFF
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock()); // 0x044D LDH (0x25), A
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock()); // 0x044F LD A, 0x77
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock()); // 0x0451 LDH (0x24), A
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock()); // 0x0453 LD HL, 0x0B8F
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock()); // 0x0456 CALL 0x02A3
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock()); // 0x02A3 LD A, L
  EXPECT_NO_THROW(sm->clock()); // 0x02A4 LD (0xD602), A
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock()); // 0x02A7 LD A, H
  EXPECT_NO_THROW(sm->clock()); // 0x02A8 LD (0xD603), A
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock()); // 0x02AB JR 0x04 (4, 0x02B1)
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock()); // 0x02B1 LD A, 0xC3
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock()); // 0x02B3 LD (0xD601), A
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock()); // 0x02B6 RET
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock()); // 0x0459 CALL 0x038E
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock()); // 0x038E PUSH HL
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock()); // 0x038F CALL 0x037B
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock()); // 0x037B POP HL
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock()); // 0x037C PUSH HL
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock()); // 0x037D PUSH AF
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock()); // 0x037E INC HL
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock()); // 0x037F INC HL
  EXPECT_NO_THROW(sm->clock());
  EXPECT_NO_THROW(sm->clock()); // 0x0380 LD A, (HL+)
  EXPECT_NO_THROW(sm->clock());
  for (int var = 0; var < 93; ++var) {
    EXPECT_NO_THROW(sm->clock()) << var;
  }
  for (int var = 0; var < 1000; ++var) {
    EXPECT_NO_THROW(sm->clock()); // 0x073E INC BC
    EXPECT_NO_THROW(sm->clock());
    EXPECT_NO_THROW(sm->clock()); // 0x073F LD A, B
    EXPECT_NO_THROW(sm->clock()); // 0x0740 OR C
    EXPECT_NO_THROW(sm->clock()); // 0x0741 JR Z, 0x06 (+6)
    EXPECT_NO_THROW(sm->clock());
    EXPECT_NO_THROW(sm->clock()); // 0x0743 LDH A, (0x44)
    EXPECT_NO_THROW(sm->clock());
    EXPECT_NO_THROW(sm->clock());
    EXPECT_NO_THROW(sm->clock()); // 0x0745 CP 0x90
    EXPECT_NO_THROW(sm->clock());
    EXPECT_NO_THROW(sm->clock()); // 0x0747 JR NZ, 0xF5 (-11, 0x0734)
    EXPECT_NO_THROW(sm->clock());
    EXPECT_NO_THROW(sm->clock());
  } // TODO: this is waiting on LY, so it won't work for now

  //-----------------------------------------------DONE-----------------------------------------------------------------
}
