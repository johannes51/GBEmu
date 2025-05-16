#ifndef MOCKTILEMAP_H
#define MOCKTILEMAP_H

#include "ppu/layer/tiledata.h"
#include "ppu/layer/tilemap.h"

class MockTileMap : public TileMap {
public:
  MockTileMap()
      : TileMap(*(IRegisterAdapter*)nullptr, *(IMemoryView*)nullptr, -1)
  {
  }
  int8_t getIndex(const TileAddress& address) const override
  {
    (void)address;
    return 0U;
  }
};

#endif // MOCKTILEMAP_H
