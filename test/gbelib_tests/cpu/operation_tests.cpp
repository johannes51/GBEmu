#include "gtest/gtest.h"

#include "cpu/operation.h"
#include "location/location.h"

#include "debug/variablebyte.h"


using namespace std;

TEST(OperationTest, testOp)
{
  Operation op;
  op.nextOpcode(Location<uint8_t>::generate(std::make_unique<VariableByte>(0x352B)));
  ASSERT_NO_THROW(op.clock());
}


