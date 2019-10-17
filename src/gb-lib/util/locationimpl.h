#ifndef LOCATIONIMPL_H
#define LOCATIONIMPL_H

#include <stdint.h>

#include "locationbyte.h"
#include "nullbyte.h"


class LocationImpl
{
public:
  uint8_t getByte() const;
  uint16_t getWord() const;

protected:
  LocationImpl(LocationByte&& lower, LocationByte&& upper = NullByte());

private:
  LocationByte& lower_;
  LocationByte& upper_;
};

#endif // LOCATIONIMPL_H
