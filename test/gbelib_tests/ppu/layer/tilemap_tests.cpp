#include "gtest/gtest.h"

#include "ppu/layer/tilemap.h"

#include "mock/mockregisteradapter.h"

#include "mem/nullbank.h"
#include "mem/rambank.h"
#include "ppu/layer/tiledata.h"

TEST(TileMapTests, Construction) { TileMap t(nullptr, nullptr, nullptr, 4); }

TEST(TileMapTests, GetTile)
{
  auto mem = std::make_shared<NullBank>(MemoryArea { 0x8000, 0x9FFF });
  auto td = std::make_unique<TileData>(MockRegisterAdapter::make(), mem);
  TileMap t(MockRegisterAdapter::make(), std::move(mem), std::move(td), 4);
  EXPECT_NO_THROW(t.getTile({ 0, 0 }));
}

TEST(TileMapTests, GetTileContent)
{
  auto mem = std::make_shared<RamBank>(MemoryArea { 0x8000, 0x9FFF });
  mem->getWord(0x8040).set(0xFFFF);
  mem->getByte(0x9800).set(4);
  auto td = std::make_unique<TileData>(MockRegisterAdapter::make(), mem);
  TileMap t(MockRegisterAdapter::make(), std::move(mem), std::move(td), 4);
  auto tile = t.getTile({ 0, 0 });

  EXPECT_EQ(tile.get({ 0, 0 }), 3);
}
