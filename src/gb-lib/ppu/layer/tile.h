#ifndef TILE_H
#define TILE_H

#include <array>
#include <cstdint>

#include "pos.h"

class Tile {
public:
  explicit Tile(std::array<uint8_t, 16> data);

  uint8_t get(const Pos& pos) { return data_.at(pos.y).at(pos.x); }

private:
  uint8_t toDataIndex(uint8_t x, uint8_t y);
  uint8_t toByteIndex(uint8_t x);
  uint8_t adjustData(uint8_t dataByte, uint8_t byteIndex);

  std::array<std::array<uint8_t, 8>, 8> data_;
};

#endif // TILE_H
