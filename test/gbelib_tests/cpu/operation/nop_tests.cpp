#include "gtest/gtest.h"

#include "cpu/operation/nop.h"
#include "location/location.h"

TEST(NopTest, testClock) {
  Nop nop;
  EXPECT_TRUE(nop.isComplete());
  EXPECT_FALSE(nop.isDone());
  EXPECT_NO_THROW(nop.clock());
  EXPECT_TRUE(nop.isDone());
  EXPECT_ANY_THROW(nop.clock());
}

TEST(NopTest, testNextOpcode) {
  Nop nop;
  EXPECT_ANY_THROW(nop.nextOpcode(LocationUP<uint8_t>()););
}

TEST(NopTest, testExecute) {
  Nop nop;
  EXPECT_ANY_THROW(nop.execute());
  EXPECT_FALSE(nop.isDone());
  EXPECT_NO_THROW(nop.clock());
  EXPECT_TRUE(nop.isDone());
  EXPECT_NO_THROW(nop.execute());
}

