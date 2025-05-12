#include "gtest/gtest.h"

#include "sys/systemmanager.h"

#include "gb_factories/gbfactory.h"

TEST(SystemManagerTest, Clock)
{
  GbFactory f { "cpu_instrs.gb", "cpu_instrs.sav" };
  const auto s = f.constructSystem();
  EXPECT_NO_THROW(s->clock());
}

TEST(SystemManagerTest, PixelBuffer)
{
  GbFactory f { "cpu_instrs.gb", "cpu_instrs.sav" };
  const auto s = f.constructSystem();
  EXPECT_NE(nullptr, s->getBuffer());
}
