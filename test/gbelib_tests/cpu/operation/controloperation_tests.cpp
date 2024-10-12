#include "gtest/gtest.h"

#include "cpu/cpuregisters.h"
#include "cpu/flagsview.h"
#include "cpu/operation/control.h"
#include "cpu/registersinterface.h"
#include "location/nulllocation.h"

TEST(ControlOperationTest, Nop)
{
  Control nop { ControlOp::Nop };
  IMemoryViewSP m;
  CpuRegisters r;

  EXPECT_TRUE(nop.isComplete());
  EXPECT_EQ(1U, nop.cycles());
  EXPECT_NO_THROW(nop.execute(r, *m));
}

TEST(NopTest, NextOpcode)
{
  Control nop { ControlOp::Nop };
  EXPECT_ANY_THROW(nop.nextOpcode(std::make_unique<NullLocation>()));
}

TEST(ControlOperationTest, Ei)
{
  Control ei { ControlOp::EI };
  IMemoryViewSP m;
  CpuRegisters r;

  r.getFlags().disableInterrupt();
  EXPECT_TRUE(ei.isComplete());
  EXPECT_EQ(1U, ei.cycles());
  EXPECT_NO_THROW(ei.execute(r, *m));
  EXPECT_TRUE(r.getFlags().interruptEnabled());
}

TEST(ControlOperationTest, Di)
{
  Control di { ControlOp::DI };
  IMemoryViewSP m;
  CpuRegisters r;

  r.getFlags().enableInterrupt();
  EXPECT_TRUE(di.isComplete());
  EXPECT_EQ(1U, di.cycles());
  EXPECT_NO_THROW(di.execute(r, *m));
  EXPECT_FALSE(r.getFlags().interruptEnabled());
}

TEST(ControlOperationTest, Halt)
{
  IMemoryViewSP m;
  CpuRegisters r;

  Control h { ControlOp::Halt };

  EXPECT_TRUE(h.isComplete());
  EXPECT_EQ(1U, h.cycles());
  EXPECT_ANY_THROW(h.execute(r, *m));
}

TEST(ControlOperationTest, Stop)
{
  IMemoryViewSP m;
  CpuRegisters r;

  Control s { ControlOp::Stop };

  EXPECT_TRUE(s.isComplete());
  EXPECT_EQ(1U, s.cycles());
  EXPECT_ANY_THROW(s.execute(r, *m));
}
