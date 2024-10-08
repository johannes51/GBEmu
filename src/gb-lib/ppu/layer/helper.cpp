#include "helper.h"

#include "../ppu_constants.h"

auto decomposePos(
    uint8_t x, uint8_t y, uint8_t scrollX /* = 0*/, uint8_t scrollY /* = 0*/) -> std::pair<TileAddress, TilePos>
{
  x += scrollX;
  x %= LcdWidth;
  y += scrollY;
  y %= LcdHeight;
  auto ta = TileAddress { static_cast<uint8_t>(x / TileSize), static_cast<uint8_t>(y / TileSize) };
  auto po = TilePos { static_cast<uint8_t>(x % TileSize), static_cast<uint8_t>(y % TileSize) };
  return { ta, po };
}
