#ifndef HELPER_H
#define HELPER_H

#include <cstdint>
#include <utility>

#include "tile.h"
#include "tilemap.h"

std::pair<TileAddress, TilePos> decomposePos(
    const uint8_t x, const uint8_t y, const uint8_t scrollX = 0, const uint8_t scrollY = 0);

size_t toFlatAddress(const TileAddress& address);

#endif // HELPER_H
