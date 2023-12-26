#include "gtest/gtest.h"

#include "ppu/layer/tiledata.h"

#include "mock/mockregisteradapter.h"

#include "mem/rambank.h"

TEST(TileDataTests, Construction) { EXPECT_NO_THROW(TileData td(nullptr, nullptr)); }

TEST(TileDataTests, GetTile)
{
  auto r = std::make_shared<RamBank>(MemoryArea { 0x8000, 0x800F });
  r->getByte(0x8001).set(0xFF);
  TileData td(MockRegisterAdapter::make(), r);
  EXPECT_NO_THROW(td.getTile(0));
}

TEST(TileDataTests, GetTileContent)
{
  auto r = std::make_shared<RamBank>(MemoryArea { 0x8000, 0x800F });
  r->getByte(0x8001).set(0xFF);
  TileData td(MockRegisterAdapter::make(), r);
  auto tile = td.getTile(0);

  EXPECT_EQ(tile.get(TilePos { 5, 0 }), 3);
}
