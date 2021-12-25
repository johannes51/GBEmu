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
    return Tile { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };
  }
};

#endif // MOCKTILEMAP_H
