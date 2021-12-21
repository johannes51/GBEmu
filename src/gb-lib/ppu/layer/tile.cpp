#include "tile.h"

#include <stdexcept>

Tile::Tile(std::array<uint8_t, TileDataSize> data)
    : data_()
{
  for (uint8_t y = 0; y < TileSize; ++y) {
    for (uint8_t x = 0; x < TileSize; ++x) {
      data_[y][x] = adjustData(data[toDataIndex(x, y)], toByteIndex(x));
    }
  }
}

auto Tile::toDataIndex(uint8_t x, uint8_t y) -> uint8_t { return (y * TileSize + x) / 4; }

auto Tile::toByteIndex(uint8_t x) -> uint8_t
{
  switch (x) {
  case 0:
  case 4:
    return 0;
    break;
  case 1:
  case 5: // NOLINT
    return 1;
    break;
  case 2:
  case 6: // NOLINT
    return 2;
    break;
  case 3:
  case 7: // NOLINT
    return 3;
    break;
  default:
    throw std::invalid_argument("bad value");
    break;
  }
}

auto Tile::adjustData(uint32_t dataByte, uint8_t byteIndex) -> uint8_t
{
  const auto offset = (3U - byteIndex) * 2U;
  return (dataByte >> offset) & 0b11U;
}
