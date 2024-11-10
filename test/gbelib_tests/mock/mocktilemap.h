#ifndef MOCKTILEMAP_H
#define MOCKTILEMAP_H

#include "ppu/layer/tiledata.h"
#include "ppu/layer/tilemap.h"

class MockTileMap : public TileMap {
public:
  MockTileMap()
      : TileMap(nullptr, nullptr, nullptr, -1)
  {
  }
  Tile getTile(const TileAddress& address) override
  {
    (void)address;
    return Tile { { 0x7C, 0x7C, 0x00, 0xC6, 0xC6, 0x00, 0x00, 0xFE, 0xC6, 0xC6, 0x00, 0xC6, 0xC6, 0x00, 0x00, 0x00 } };
  }
};

#endif // MOCKTILEMAP_H
