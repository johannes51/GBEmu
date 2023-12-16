#include "gtest/gtest.h"

#include "apu/apu.h"

TEST(ApuTest, Construction) { EXPECT_NO_THROW(Apu a(nullptr)); }

TEST(ApuTest, Clock)
{
  Apu a(nullptr);
  EXPECT_NO_THROW(a.clock());
}
