#ifndef BIT_MANIP_H
#define BIT_MANIP_H

#include <cstdint>

#include "ops.h"

class Location8;
class Location16;

namespace ops {

OpResult bit(const Location8& location, uint8_t bitPos);
OpResult bit(const Location16& location, uint8_t bitPos);

OpResult set(Location8& location, uint8_t bitPos);

OpResult reset(Location8& location, uint8_t bitPos);

} // namespace ops

#endif // BIT_MANIP_H
