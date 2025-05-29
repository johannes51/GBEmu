#ifndef BIT_MANIP_H
#define BIT_MANIP_H

#include <cstdint>

#include "ops.h"

class ILocation8;
class ILocation16;

namespace ops {

OpResult bit(const ILocation8& location, uint8_t bitPos);
OpResult bit(const ILocation16& location, uint8_t bitPos);

OpResult set(ILocation8& location, uint8_t bitPos);

OpResult reset(ILocation8& location, uint8_t bitPos);

} // namespace ops

#endif // BIT_MANIP_H
