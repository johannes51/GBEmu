#include "palette.h"

#include <stdexcept>

#include <type_traits>

auto Palette::getColor(uint8_t index) -> Colors
{
  if (index > 3) {
    throw std::invalid_argument("bad color index");
  }
  const auto offset = (3U - index) * 2U;
  auto colorCode = (static_cast<unsigned int>(bgp_->get()) >> offset) & 0b11U; // suppress promotion to signed
  switch (colorCode) {
  case 0:
    return Colors::White;
    break;
  case 1:
    return Colors::LightGray;
    break;
  case 2:
    return Colors::DarnkGray;
    break;
  case 3:
    return Colors::Black;
    break;
  default:
    throw std::invalid_argument("couldn't calculate color, should not happen");
    break;
  }
}
