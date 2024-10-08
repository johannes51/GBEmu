#include "gtest/gtest.h"

#include "ppu/layer/tilemap.h"

#include "mock/mockregisteradapter.h"
#include "mock/testbank.h"

#include "mem/nullbank.h"
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
  auto mem = std::make_shared<TestBank>(MemoryArea { 0x8000, 0x9FFF });
  *mem->getLocation(0x8040) = uint16_t(0xFFFF);
//  *mem->getLocation(0x9800) = uint8_t(4);
//  auto td = std::make_unique<TileData>(MockRegisterAdapter::make(), mem);
//  TileMap t(MockRegisterAdapter::make(), std::move(mem), std::move(td), 4);
//  auto tile = t.getTile({ 0, 0 });

//  EXPECT_EQ(tile.get({ 0, 0 }), 3);
}
