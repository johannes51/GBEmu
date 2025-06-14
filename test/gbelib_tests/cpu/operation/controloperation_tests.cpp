#include "gtest/gtest.h"

#include "mock/testbank.h"

#include "cpu/operation/control.h"
#include "cpu/registers/cpuregisters.h"
#include "cpu/registers/flagsview.h"
#include "cpu/registers/registersinterface.h"
#include "mem/rest/zerolocation.h"

TEST(ControlOperationTest, Nop)
{
  Control nop { ControlOp::Nop };
  CpuRegisters r;
  auto mem = TestBank { { .from = 0x0000, .to = 0xFFFF } };

  EXPECT_TRUE(nop.isComplete());
  EXPECT_EQ(1U, nop.cycles());
  EXPECT_NO_THROW(nop.execute(r, mem));
}

TEST(NopTest, NextOpcode)
{
  Control nop { ControlOp::Nop };
  ZeroLocation l;
  EXPECT_ANY_THROW(nop.nextOpcode(l));
}

TEST(ControlOperationTest, Ei)
{
  Control ei { ControlOp::EI };
  CpuRegisters r;
  auto mem = TestBank { { .from = 0x0000, .to = 0xFFFF } };

  r.getFlags().disableInterrupt();
  EXPECT_TRUE(ei.isComplete());
  EXPECT_EQ(1U, ei.cycles());
  EXPECT_NO_THROW(ei.execute(r, mem));
  EXPECT_TRUE(r.getFlags().interruptEnabled());
}

TEST(ControlOperationTest, Di)
{
  Control di { ControlOp::DI };
  CpuRegisters r;
  auto mem = TestBank { { .from = 0x0000, .to = 0xFFFF } };

  r.getFlags().enableInterrupt();
  EXPECT_TRUE(di.isComplete());
  EXPECT_EQ(1U, di.cycles());
  EXPECT_NO_THROW(di.execute(r, mem));
  EXPECT_FALSE(r.getFlags().interruptEnabled());
}

TEST(ControlOperationTest, Halt)
{
  CpuRegisters r;
  auto mem = TestBank { { .from = 0x0000, .to = 0xFFFF } };

  Control h { ControlOp::Halt };

  EXPECT_TRUE(h.isComplete());
  EXPECT_EQ(1U, h.cycles());
  // EXPECT_ANY_THROW(h.execute(r, mem)); // TODO: ganz implementieren
}

TEST(ControlOperationTest, Stop)
{
  CpuRegisters r;
  auto mem = TestBank { { .from = 0x0000, .to = 0xFFFF } };

  Control s { ControlOp::Stop };

  EXPECT_TRUE(s.isComplete());
  EXPECT_EQ(1U, s.cycles());
  EXPECT_ANY_THROW(s.execute(r, mem));
}
