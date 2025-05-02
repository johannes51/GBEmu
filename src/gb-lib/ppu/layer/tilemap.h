#ifndef TILEMAP_H
#define TILEMAP_H

#include "mem/imemoryview.h"
#include "mem/registers/iregisteradapter.h"
#include "tile.h"
#include "tiledata.h"

struct TileAddress {
  uint8_t x;
  uint8_t y;
};

class TileMap {
public:
  explicit TileMap(IRegisterAdapterSP lcdc, IMemoryViewSP mem, TileDataUP tiles, uint8_t bit);
  virtual ~TileMap();

  virtual Tile getTile(const TileAddress& address);

private:
  int8_t getIndex(uint8_t flatAddress) const;
  address_type baseAdress() const;

  IRegisterAdapterSP lcdc_;
  IMemoryViewSP mem_;

  TileDataUP tiles_;

  const uint8_t bit_;
};

using TileMapUP = std::unique_ptr<TileMap>;

#endif // TILEMAP_H
