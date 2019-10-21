#ifndef LOCATIONBYTE_H
#define LOCATIONBYTE_H

#include <stdint.h>

#include "defines.h"

class LocationByte {
public:
  LocationByte() = default;
  virtual ~LocationByte() = default;
  DISABLE_COPY_AND_MOVE(LocationByte)

  virtual uint8_t get() const = 0;
  virtual void set(const uint8_t &value) = 0;
};

#endif // LOCATIONBYTE_H
