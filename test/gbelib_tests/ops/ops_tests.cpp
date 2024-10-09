#include "gtest/gtest.h"

#include "ops/ops.h"

TEST(OpsTest, Construction)
{
  ops::OpResult a;

  EXPECT_EQ(ops::FlagResult::NoChange, a.z);
  EXPECT_EQ(ops::FlagResult::NoChange, a.n);
  EXPECT_EQ(ops::FlagResult::NoChange, a.h);
  EXPECT_EQ(ops::FlagResult::NoChange, a.c);

  ops::OpResult b { ops::FlagResult::Set, ops::FlagResult::Reset, ops::FlagResult::Set, ops::FlagResult::NoChange };

  EXPECT_EQ(ops::FlagResult::Set, b.z);
  EXPECT_EQ(ops::FlagResult::Reset, b.n);
  EXPECT_EQ(ops::FlagResult::Set, b.h);
  EXPECT_EQ(ops::FlagResult::NoChange, b.c);
}

TEST(OpsTest, Comparison)
{
  ops::OpResult ex { ops::FlagResult::Set, ops::FlagResult::Reset, ops::FlagResult::Set, ops::FlagResult::NoChange };

  ops::OpResult a;

  EXPECT_FALSE(ex == a);

  a.z = ops::FlagResult::Set;
  a.n = ops::FlagResult::Reset;
  a.h = ops::FlagResult::Set;
  a.c = ops::FlagResult::NoChange;

  EXPECT_TRUE(ex == a);
}
