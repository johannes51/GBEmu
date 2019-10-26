#include "gtest/gtest.h"

#include "cpu/operation/nop.h"
#include "cpu/registersinterface.h"
#include "location/location.h"

TEST(NopTest, testClock)
{
  Nop nop;
  EXPECT_TRUE(nop.isComplete());
  EXPECT_FALSE(nop.isDone());
  EXPECT_NO_THROW(nop.clock());
  EXPECT_TRUE(nop.isDone());
  EXPECT_ANY_THROW(nop.clock());
}

TEST(NopTest, testNextOpcode)
{
  Nop nop;
  EXPECT_ANY_THROW(nop.nextOpcode(Location<uint8_t>::generate(std::make_unique<NullByte>())););
}

TEST(NopTest, testExecute)
{
  Nop nop;
  RegistersInterfaceUP r;
  EXPECT_ANY_THROW(nop.execute(*r));
  EXPECT_FALSE(nop.isDone());
  EXPECT_NO_THROW(nop.clock());
  EXPECT_TRUE(nop.isDone());
  EXPECT_NO_THROW(nop.execute(*r));
}
