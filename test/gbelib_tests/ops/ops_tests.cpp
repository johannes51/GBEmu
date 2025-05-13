#include "gtest/gtest.h"

#include "ops/ops.h"

TEST(OpsTest, Construction)
{
  ops::OpResult a { ops::FlagResult::Set, ops::FlagResult::Reset, ops::FlagResult::Set, ops::FlagResult::NoChange };

  EXPECT_EQ(ops::FlagResult::Set, a.z);
  EXPECT_EQ(ops::FlagResult::Reset, a.n);
  EXPECT_EQ(ops::FlagResult::Set, a.h);
  EXPECT_EQ(ops::FlagResult::NoChange, a.c);
}

TEST(OpsTest, Comparison)
{
  ops::OpResult ex { ops::FlagResult::Set, ops::FlagResult::Reset, ops::FlagResult::Set, ops::FlagResult::NoChange };

  ops::OpResult a; // NOLINT intentionally uninititalized

  a.z = ops::FlagResult::Set;
  a.n = ops::FlagResult::Reset;
  a.h = ops::FlagResult::Set;
  a.c = ops::FlagResult::NoChange;

  EXPECT_TRUE(ex == a);
}
