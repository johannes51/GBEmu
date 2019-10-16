#ifndef LOCATIONIMPL_H
#define LOCATIONIMPL_H

#include <stdint.h>

#include "locationbyte.h"


class LocationImpl
{
public:
  LocationImpl(LocationByte&& lower, LocationByte&& upper);

  uint8_t getByte() const;
  uint16_t getWord() const;
};

#endif // LOCATIONIMPL_H
