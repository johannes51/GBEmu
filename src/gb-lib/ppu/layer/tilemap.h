#ifndef TILEMAP_H
#define TILEMAP_H

#include "mem/imemoryview.h"
#include "mem/registers/iregisteradapter.h"

struct TileAddress {
  uint8_t x;
  uint8_t y;
};

class TileMap {
public:
  explicit TileMap(IRegisterAdapterSP lcdc, IMemoryViewSP mem, uint8_t bit);
  virtual ~TileMap();

  virtual int8_t getIndex(const TileAddress& address) const;

private:
  address_type baseAdress() const;

  IRegisterAdapterSP lcdc_;
  IMemoryViewSP mem_;

  const uint8_t bit_;
};

using TileMapUP = std::unique_ptr<TileMap>;

#endif // TILEMAP_H
