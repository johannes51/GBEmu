#ifndef MOCKTILEMAP_H
#define MOCKTILEMAP_H

#include "ppu/layer/tiledata.h"
#include "ppu/layer/tilemap.h"

#include "mock/testbank.h"

class MockTileMap : public TileMap {
public:
  MockTileMap()
      : TileMap(*fakeReg, TestBank::staticBank(), -1)
  {
  }
  int8_t getIndex(const TileAddress& address) const override
  {
    (void)address;
    return 0U;
  }

private:
  static IRegisterAdapterUP fakeReg;
};

#endif // MOCKTILEMAP_H
