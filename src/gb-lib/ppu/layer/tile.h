#ifndef TILE_H
#define TILE_H

#include <array>
#include <cstdint>

#include "../ppu_constants.h"
#include "pos.h"

class Tile {
public:
  explicit Tile(std::array<uint8_t, TileDataSize> data);

  uint8_t get(const Pos& pos) { return data_.at(pos.y).at(pos.x); }

private:
  static uint8_t toDataIndex(uint8_t x, uint8_t y);
  static uint8_t toByteIndex(uint8_t x);
  static uint8_t adjustData(uint32_t dataByte, uint8_t byteIndex);

  std::array<std::array<uint8_t, TileSize>, TileSize> data_;
};

#endif // TILE_H
