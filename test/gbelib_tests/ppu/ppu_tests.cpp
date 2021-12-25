#include "gtest/gtest.h"

#include "ppu/ppu.h"

TEST(PpuTest, Construction) { EXPECT_NO_THROW(Ppu p(nullptr)); }

TEST(PpuTest, Clock)
{
  Ppu p(nullptr);
  EXPECT_NO_THROW(p.clock());
}
