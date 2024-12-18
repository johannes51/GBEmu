#include "gtest/gtest.h"

#include "cpu/operation/operation.h"

#include "cpu/cpuregisters.h"
#include "cpu/flagsview.h"
#include "cpu/operation/control.h"

TEST(OperationTest, Direct)
{
  CpuRegisters r;
  Control o { ControlOp::Nop };

  EXPECT_NO_THROW(o.showFlags(*FlagsViewUP {}));
}
