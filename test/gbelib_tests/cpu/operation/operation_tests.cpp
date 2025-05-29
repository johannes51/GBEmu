#include "gtest/gtest.h"

#include "mock/mockflags.h"

#include "cpu/operation/operation.h"

#include "cpu/operation/control.h"
#include "cpu/registers/cpuregisters.h"

TEST(OperationTest, Direct)
{
  CpuRegisters r;
  Control o { ControlOp::Nop };

  auto fv = MockFlags {};

  EXPECT_NO_THROW(o.showFlags(fv));
}
