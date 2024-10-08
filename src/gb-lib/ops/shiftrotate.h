#ifndef SHIFT_ROTATE_H
#define SHIFT_ROTATE_H

#include <climits>
#include <cstdint>

#include "ops.h"

class Location;

namespace ops {

namespace detail {

constexpr uint8_t BitSize = sizeof(uint8_t) * CHAR_BIT;
constexpr uint8_t MsbMask = 0b10000000;
constexpr uint8_t LsbMask = 0b00000001;

} // namespace detail

OpResult rr(Location& location, bool carry);

OpResult rrc(Location& location);

OpResult rl(Location& location, bool carry);

OpResult rlc(Location& location);

OpResult sra(Location& location);

OpResult sla(Location& location);

OpResult srl(Location& location);

OpResult swap(Location& location);

} // namespace ops

#endif // SHIFT_ROTATE_H
