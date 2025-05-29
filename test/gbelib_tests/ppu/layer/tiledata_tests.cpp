#include "gtest/gtest.h"

#include "ppu/layer/tiledata.h"

#include "mock/mockregisteradapter.h"
#include "mock/testbank.h"

#include "mem/rest/zerobank.h"

TEST(TileDataTests, Construction)
{
  auto mem = std::make_shared<ZeroBank>(MemoryArea { 0x8000, 0x9FFF });
  EXPECT_NO_THROW(TileData td(*MockRegisterAdapter::make(), *mem));
}

TEST(TileDataTests, GetTile)
{
  auto r = std::make_unique<TestBank>(MemoryArea { 0x8000, 0x800F });
  r->getLocation8(0x8001) = uint8_t { 0xFF };
  auto lcdc = MockRegisterAdapter::make();
  TileData td(*lcdc, *r);
  EXPECT_NO_THROW(td.getTile(0));
}

TEST(TileDataTests, GetTileContent)
{
  auto r = std::make_unique<TestBank>(MemoryArea { 0x8000, 0x800F });
  r->getLocation8(0x8000) = uint8_t { 0xFF };
  r->getLocation8(0x8001) = uint8_t { 0xFF };
  auto lcdc = MockRegisterAdapter::make();
  TileData td(*lcdc, *r);
  auto tile = td.getTile(0);

  EXPECT_EQ(tile.get(TilePos { 5, 0 }), 3);
}
