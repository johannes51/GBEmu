#include "gtest/gtest.h"

#include "cpu/cpuregisters.h"
#include "cpu/flagsview.h"
#include "cpu/operation/control.h"
#include "cpu/registersinterface.h"
#include "location/location.h"

TEST(ControlTest, testNop)
{
  Control nop { ControlOp::Nop };
  RegistersInterfaceUP r;
  IMemoryViewSP m;

  EXPECT_TRUE(nop.isComplete());
  EXPECT_EQ(1, nop.cycles());
  EXPECT_NO_THROW(nop.execute(*r, *m));
}

TEST(NopTest, testNextOpcode)
{
  Control nop { ControlOp::Nop };
  EXPECT_ANY_THROW(nop.nextOpcode(Location<uint8_t>::generate(std::make_unique<NullByte>())));
}

TEST(ControlTest, testEi)
{
  Control ei { ControlOp::EI };
  IMemoryViewSP m;
  CpuRegisters r;

  r.getFlags().disableInterrupt();
  EXPECT_TRUE(ei.isComplete());
  EXPECT_EQ(1, ei.cycles());
  EXPECT_NO_THROW(ei.execute(r, *m));
  EXPECT_TRUE(r.getFlags().interruptEnabled());
}

TEST(ControlTest, testDi)
{
  Control di { ControlOp::DI };
  IMemoryViewSP m;
  CpuRegisters r;

  r.getFlags().enableInterrupt();
  EXPECT_TRUE(di.isComplete());
  EXPECT_EQ(1, di.cycles());
  EXPECT_NO_THROW(di.execute(r, *m));
  EXPECT_FALSE(r.getFlags().interruptEnabled());
}