#ifndef TILEDATA_H
#define TILEDATA_H

#include <memory>

#include "mem/imemoryview.h"
#include "mem/registers/iregisteradapter.h"
#include "tile.h"

class TileData {
public:
  explicit TileData(IRegisterAdapterSP lcdc, IMemoryViewSP mem, int8_t bit = -1);
  virtual ~TileData() = default;

  virtual Tile getTile(int16_t index);

private:
  address_type baseAdress() const;
  std::array<uint8_t, 16> loadTile(address_type address) const;

  IRegisterAdapterSP lcdc_;
  IMemoryViewSP mem_;

  const int8_t Bit_;
};

using TileDataUP = std::unique_ptr<TileData>;

#endif // TILEDATA_H
