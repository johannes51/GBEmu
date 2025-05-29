#ifndef MOCKTILEDATA_H
#define MOCKTILEDATA_H

#include "ppu/layer/tiledata.h"

#include "mockregisteradapter.h"
#include "testbank.h"

#include "io/ioregister.h"

class MockTileData : public TileData {
public:
  MockTileData(Tile tile = Tile { {} })
      : TileData(fakeReg, TestBank::staticBank())
      , tile_(tile) {};

  Tile getTile(int16_t index) override
  {
    (void)index;
    return tile_;
  }

private:
  Tile tile_;

  static IoRegister fakeReg;
};

#endif // MOCKTILEDATA_H
