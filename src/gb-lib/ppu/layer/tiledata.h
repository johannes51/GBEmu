#ifndef TILEDATA_H
#define TILEDATA_H

#include "mem/imemoryview.h"
#include "mem/registers/iregisteradapter.h"
#include "tile.h"

class Tile;
class TileData {
public:
  explicit TileData(IRegisterAdapterSP lcdc, IMemoryViewSP mem);

  Tile getTile(uint8_t index);

private:
  address_type baseAdress() const;
  std::array<uint8_t, 16> loadTile(address_type address) const;

  IRegisterAdapterSP lcdc_;
  IMemoryViewSP mem_;
};

#endif // TILEDATA_H
