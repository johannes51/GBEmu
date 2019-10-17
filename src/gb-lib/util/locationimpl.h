#ifndef LOCATIONIMPL_H
#define LOCATIONIMPL_H

#include <stdint.h>

#include "util_defines.h"


class LocationImpl
{
public:
  uint8_t getByte() const;
  uint16_t getWord() const;

protected:
  LocationImpl(LocationByteUP lower, LocationByteUP upper);

private:
  LocationByteUP lower_;
  LocationByteUP upper_;
};

#endif // LOCATIONIMPL_H
