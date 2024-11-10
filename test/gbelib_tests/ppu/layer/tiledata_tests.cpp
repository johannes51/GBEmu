#include "gtest/gtest.h"

#include "ppu/layer/tiledata.h"

#include "mock/mockregisteradapter.h"

#include "mock/testbank.h"

TEST(TileDataTests, Construction) { EXPECT_NO_THROW(TileData td(nullptr, nullptr)); }

TEST(TileDataTests, GetTile)
{
  auto r = std::make_shared<TestBank>(MemoryArea { 0x8000, 0x800F });
  *r->getLocation(0x8001) = uint8_t { 0xFF };
  TileData td(MockRegisterAdapter::make(), r);
  EXPECT_NO_THROW(td.getTile(0));
}

TEST(TileDataTests, GetTileContent)
{
  auto r = std::make_shared<TestBank>(MemoryArea { 0x8000, 0x800F });
  *r->getLocation(0x8000) = uint8_t { 0xFF };
  *r->getLocation(0x8001) = uint8_t { 0xFF };
  TileData td(MockRegisterAdapter::make(), r);
  auto tile = td.getTile(0);

  EXPECT_EQ(tile.get(TilePos { 5, 0 }), 3);
}
