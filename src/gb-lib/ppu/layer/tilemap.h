#ifndef TILEMAP_H
#define TILEMAP_H

#include "mem/imemoryview.h"
#include "mem/registers/iregisteradapter.h"
#include "tile.h"
#include "tileaddress.h"

class TileData;

class TileMap {
public:
  explicit TileMap(IRegisterAdapterSP lcdc, IMemoryViewSP mem, std::unique_ptr<TileData> tiles, uint8_t bit);
  ~TileMap();

  Tile getTile(const TileAddress& address);

private:
  static uint8_t toFlatAddress(const TileAddress& address);
  uint8_t getIndex(uint8_t flatAddress) const;
  address_type baseAdress() const;

  IRegisterAdapterSP lcdc_;
  IMemoryViewSP mem_;

  std::unique_ptr<TileData> tiles_;

  const uint8_t bit_;
};

#endif // TILEMAP_H
