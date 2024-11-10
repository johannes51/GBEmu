#ifndef TILE_H
#define TILE_H

#include <array>
#include <cstdint>

#include "../ppu_constants.h"

struct TilePos {
  uint8_t x;
  uint8_t y;
};

class Tile {
public:
  explicit Tile(std::array<uint8_t, TileDataSize> data);

  uint8_t get(const TilePos& pos) const { return data_.at(pos.y).at(pos.x); }

private:
  std::array<std::array<uint8_t, TileSize>, TileSize> data_;

  static uint8_t extractPixel(const std::array<uint8_t, TileDataSize>& data, uint8_t x, uint8_t y);
};

#endif // TILE_H
