#ifndef SHIFT_ROTATE_H
#define SHIFT_ROTATE_H

#include <climits>
#include <cstdint>

#include "ops.h"

class Location8;

namespace ops {

namespace detail {

constexpr uint8_t BitSize = sizeof(uint8_t) * CHAR_BIT;
constexpr uint8_t MsbMask = 0b10000000;
constexpr uint8_t LsbMask = 0b00000001;

} // namespace detail

OpResult rr(Location8& location, bool carry);

OpResult rrc(Location8& location);

OpResult rl(Location8& location, bool carry);

OpResult rlc(Location8& location);

OpResult sra(Location8& location);

OpResult sla(Location8& location);

OpResult srl(Location8& location);

OpResult swap(Location8& location);

} // namespace ops

#endif // SHIFT_ROTATE_H
