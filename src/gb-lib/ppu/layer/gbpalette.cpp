#include "gbpalette.h"

#include <stdexcept>

#include "util/helpers.h"

auto GbPalette::getColor(uint8_t index) -> GbColors
{
  if (index > 3) {
    throw std::invalid_argument("bad color index");
  }
  auto colorCode = hlp::getBits(bgp_.getByte(), index * 2U, 2U);
  switch (colorCode) {
  case 0:
    return GbColors::White;
    break;
  case 1:
    return GbColors::LightGray;
    break;
  case 2:
    return GbColors::DarkGray;
    break;
  case 3:
    return GbColors::Black;
    break;
  default:
    throw std::invalid_argument("couldn't calculate color, should not happen");
    break;
  }
}
