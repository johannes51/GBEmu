#include "gtest/gtest.h"

#include <fstream>

#include "sys/systemmanager.h"
#include "gb_factories/memoryfactory.h"
#include "gb_factories/cartloader.h"

TEST(SystemManagerTest, testClock) {
  gb::MemoryFactory m(std::make_unique<gb::CartLoader>(std::ifstream{"Tetris.gb", std::ios_base::binary},
                                                       std::fstream{"Tetris.sav", std::ios_base::binary}
                                                       ));
  SystemManager s(m.constructMemoryLayout());
  EXPECT_NO_THROW(s.clock());
}

