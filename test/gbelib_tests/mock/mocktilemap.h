#ifndef MOCKTILEMAP_H
#define MOCKTILEMAP_H

#include "ppu/layer/tilemap.h"

#include "mock/testbank.h"

#include "io/ioregister.h"
#include "ppu/layer/tiledata.h"

class MockTileMap : public TileMap {
public:
  MockTileMap()
      : TileMap(fakeReg, TestBank::staticBank(), -1)
  {
  }
  int8_t getIndex(const TileAddress& address) const override
  {
    (void)address;
    return 0U;
  }

private:
  static IoRegister fakeReg;
};

#endif // MOCKTILEMAP_H
