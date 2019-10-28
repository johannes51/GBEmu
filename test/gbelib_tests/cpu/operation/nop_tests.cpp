#include "gtest/gtest.h"

#include "cpu/operation/nop.h"
#include "cpu/registersinterface.h"
#include "location/location.h"

TEST(NopTest, test)
{
  Nop nop;
  RegistersInterfaceUP r;
  IMemoryViewSP m;

  EXPECT_TRUE(nop.isComplete());
  EXPECT_EQ(1, nop.cycles());
  EXPECT_NO_THROW(nop.execute(*r, *m););
}

TEST(NopTest, testNextOpcode)
{
  Nop nop;
  EXPECT_ANY_THROW(nop.nextOpcode(Location<uint8_t>::generate(std::make_unique<NullByte>())););
}
