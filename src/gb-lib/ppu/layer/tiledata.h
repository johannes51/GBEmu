#ifndef TILEDATA_H
#define TILEDATA_H

#include <memory>

#include "io/iregisteradapter.h"
#include "mem/imemoryview.h"
#include "tile.h"

class TileData {
public:
  explicit TileData(const IRegisterAdapter& lcdc, IMemoryView& mem, int8_t bit = -1);
  virtual ~TileData() = default;

  virtual Tile getTile(int16_t index);

private:
  address_type baseAdress() const;
  std::array<uint8_t, 16> loadTile(address_type address) const;

  const IRegisterAdapter& lcdc_;
  IMemoryView& mem_;

  const int8_t Bit_;
};

using TileDataUP = std::unique_ptr<TileData>;

#endif // TILEDATA_H
