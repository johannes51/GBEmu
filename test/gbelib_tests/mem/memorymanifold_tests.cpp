#include "gtest/gtest.h"

#include "mem/common/memorymanifold.h"
#include "mem/location8.h"
#include "mem/rest/nullbank.h"

TEST(MemoryManifoldTest, AddSubmanager1)
{
  MemoryManifold m;
  m.addSubManager(std::make_unique<NullBank>(MemoryArea { 1, 15 }));
  m.addSubManager(std::make_unique<NullBank>(MemoryArea { 32, 63 }));

  EXPECT_EQ(2, m.availableAreas().size());
  EXPECT_ANY_THROW(m.getLocation8(0));
  EXPECT_NO_THROW(m.getLocation8(5));
  EXPECT_NO_THROW(m.getLocation8(15));
  EXPECT_ANY_THROW(m.getLocation8(27));
  EXPECT_NO_THROW(m.getLocation8(32));
  EXPECT_NO_THROW(m.getLocation8(50));
  EXPECT_NO_THROW(m.getLocation8(63));
  EXPECT_ANY_THROW(m.getLocation8(64));
}

TEST(MemoryManifoldTest, AddSubmanager2)
{
  MemoryManifold m;
  m.addSubManager(std::make_unique<NullBank>(MemoryArea { 1, 15 }));
  EXPECT_ANY_THROW(m.addSubManager(std::make_unique<NullBank>(MemoryArea { 15, 63 })));
  EXPECT_NO_THROW(m.addSubManager(std::make_unique<NullBank>(MemoryArea { 16, 63 })));
}

TEST(MemoryManifoldTest, AvailableAreas)
{
  MemoryManifold m;
  m.addSubManager(std::make_unique<NullBank>(MemoryArea { 1, 15 }));
  m.addSubManager(std::make_unique<NullBank>(MemoryArea { 16, 63 }));

  auto available = m.availableAreas();
  EXPECT_EQ(2, available.size());
  EXPECT_NE(available.end(), std::find(available.begin(), available.end(), MemoryArea { 1, 15 }));
  EXPECT_NE(available.end(), std::find(available.begin(), available.end(), MemoryArea { 16, 63 }));
}
