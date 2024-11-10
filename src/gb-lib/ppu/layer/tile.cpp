#include "tile.h"

#include "util/helpers.h"

Tile::Tile(std::array<uint8_t, TileDataSize> data)
    : data_()
{
  for (uint8_t y = 0; y < TileSize; ++y) {
    for (uint8_t x = 0; x < TileSize; ++x) {
      data_[y][x] = extractPixel(data, x, y);
    }
  }
}

auto Tile::extractPixel(const std::array<uint8_t, TileDataSize>& data, uint8_t x, uint8_t y) -> uint8_t
{
  const auto dataIndex = y * 2U;
  const auto lsb = hlp::checkBit(data[dataIndex], 7U - x) ? 0b1U : 0b0U; // DON'T
  const auto msb = hlp::checkBit(data[dataIndex + 1U], 7U - x) ? 0b10U : 0b00U; // ASK (GB 2BPP)
  return msb | lsb;
}
