#include "helper.h"

auto decomposePos(uint8_t x, uint8_t y, uint8_t scrollX /* = 0*/, uint8_t scrollY /* = 0*/)
    -> std::pair<TileAddress, Pos>
{
  x += scrollX;
  x %= 160;
  y += scrollY;
  y %= 144;
  auto ta = TileAddress { static_cast<uint8_t>(x / 8U), static_cast<uint8_t>(y / 8U) };
  auto po = Pos { static_cast<uint8_t>(x % 8U), static_cast<uint8_t>(y % 8U) };
  return { ta, po };
}
