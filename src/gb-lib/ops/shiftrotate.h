#ifndef SHIFT_ROTATE_H
#define SHIFT_ROTATE_H

#include <climits>
#include <cstdint>

#include "ops.h"

class ILocation8;

namespace ops {

namespace detail {

constexpr uint8_t BitSize = sizeof(uint8_t) * CHAR_BIT;
constexpr uint8_t MsbMask = 0b10000000;
constexpr uint8_t LsbMask = 0b00000001;

} // namespace detail

OpResult rr(ILocation8& location);
OpResult rr(ILocation8& location, bool carry);

OpResult rl(ILocation8& location);
OpResult rl(ILocation8& location, bool carry);

OpResult sra(ILocation8& location);
OpResult sla(ILocation8& location);
OpResult srl(ILocation8& location);

OpResult swap(ILocation8& location);

} // namespace ops

#endif // SHIFT_ROTATE_H
