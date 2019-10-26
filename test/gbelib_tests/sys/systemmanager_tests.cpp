#include "gtest/gtest.h"

#include <fstream>

#include "gb_factories/cartloader.h"
#include "gb_factories/memoryfactory.h"
#include "sys/systemmanager.h"

TEST(SystemManagerTest, testClock)
{
  gb::MemoryFactory m(std::make_unique<gb::CartLoader>("Tetris.gb", "Tetris.sav"));
  SystemManager s(m.constructMemoryLayout());
  EXPECT_NO_THROW(s.clock());
}
