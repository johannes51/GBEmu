#include "tile.h"

#include <stdexcept>

Tile::Tile(std::array<uint8_t, 16> data)
    : data_()
{
  for (uint8_t y = 0; y < 8; ++y) {
    for (uint8_t x = 0; x < 8; ++x) {
      data_[y][x] = adjustData(data[toDataIndex(x, y)], toByteIndex(x));
    }
  }
}

uint8_t Tile::toDataIndex(uint8_t x, uint8_t y) { return (y * 8 + x) / 4; }

uint8_t Tile::toByteIndex(uint8_t x)
{
  switch (x) {
  case 0:
  case 4:
    return 0;
    break;
  case 1:
  case 5:
    return 1;
    break;
  case 2:
  case 6:
    return 2;
    break;
  case 3:
  case 7:
    return 3;
    break;
  default:
    throw std::invalid_argument("bad value");
    break;
  }
}

uint8_t Tile::adjustData(uint8_t dataByte, uint8_t byteIndex)
{
  const auto offset = (3 - byteIndex) * 2;
  return (dataByte >> offset) & 0b11;
}
