#ifndef BIT_MANIP_H
#define BIT_MANIP_H

#include <cstdint>

#include "ops.h"

class Location;

namespace ops {

OpResult bit(Location& location, uint8_t bitPos);

OpResult set(Location& location, uint8_t bitPos);

OpResult reset(Location& location, uint8_t bitPos);

} // namespace ops

#endif // BIT_MANIP_H
