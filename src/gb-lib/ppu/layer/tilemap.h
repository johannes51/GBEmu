#ifndef TILEMAP_H
#define TILEMAP_H

#include "mem/imemoryview.h"
#include "mem/registers/iregisteradapter.h"
#include "tile.h"

class TileData;

struct TileAddress {
  uint8_t x;
  uint8_t y;
};

class TileMap {
public:
  explicit TileMap(IRegisterAdapterSP lcdc, IMemoryViewSP mem);
  ~TileMap();

  Tile getTile(const TileAddress& address);

private:
  uint8_t toFlatAddress(const TileAddress& address);
  uint8_t getIndex(uint8_t flatAddress) const;
  address_type baseAdress() const;

  IRegisterAdapterSP lcdc_;
  IMemoryViewSP mem_;

  std::unique_ptr<TileData> tiles_;
};

#endif // TILEMAP_H
