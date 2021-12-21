#ifndef TILEDATA_H
#define TILEDATA_H

#include "location/location.h"
#include "mem/imemoryview.h"
#include "mem/registers/iregisteradapter.h"
#include "tile.h"

class TileData {
public:
  explicit TileData(IRegisterAdapterSP lcdc, IMemoryViewSP mem, int8_t bit = -1);

  Tile getTile(uint8_t index);

private:
  address_type baseAdress() const;
  std::array<uint8_t, 16> loadTile(address_type address) const;

  IRegisterAdapterSP lcdc_;
  IMemoryViewSP mem_;

  const int8_t Bit_;
  static constexpr address_type SetBaseAddress = 0x8000;
  static constexpr address_type ResetBaseAddress = 0x8800;
};

#endif // TILEDATA_H
