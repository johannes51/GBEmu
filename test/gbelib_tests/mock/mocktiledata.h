#ifndef MOCKTILEDATA_H
#define MOCKTILEDATA_H

#include "ppu/layer/tiledata.h"

class MockTileData : public TileData {
public:
  MockTileData(Tile tile = Tile { {} })
      : TileData(*(IRegisterAdapter*)nullptr, *(IMemoryView*)nullptr)
      , tile_(tile) {};

  Tile getTile(int16_t index) override
  {
    (void)index;
    return tile_;
  }

private:
  Tile tile_;
};

#endif // MOCKTILEDATA_H
