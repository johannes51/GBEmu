#ifndef HELPER_H
#define HELPER_H

#include <cstdint>
#include <utility>

#include "pos.h"
#include "tileaddress.h"

std::pair<TileAddress, Pos> decomposePos(uint8_t x, uint8_t y, uint8_t scrollX = 0, uint8_t scrollY = 0);

#endif // HELPER_H
