#include "helper.h"

#include "../ppu_constants.h"

auto decomposePos(const uint8_t x, const uint8_t y, const uint8_t scrollX /* = 0*/,
    const uint8_t scrollY /* = 0*/) -> std::pair<TileAddress, TilePos>
{
  auto totalX = (x + scrollX) % 256U; // NOLINT
  auto totalY = (y + scrollY) % 256U; // NOLINT
  auto ta = TileAddress { static_cast<uint8_t>(totalX / TileSize), static_cast<uint8_t>(totalY / TileSize) };
  auto po = TilePos { static_cast<uint8_t>(totalX % TileSize), static_cast<uint8_t>(totalY % TileSize) };
  return { ta, po };
}

auto toFlatAddress(const TileAddress& address) -> size_t { return (address.y * TileMapSize) + address.x; }
