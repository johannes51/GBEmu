#ifndef LOCATIONBYTE_H
#define LOCATIONBYTE_H

#include <stdint.h>

class LocationByte {
public:
  LocationByte();
  virtual ~LocationByte();

  virtual uint8_t operator*() = 0;
  virtual LocationByte &operator<<(const uint8_t &value) = 0;
};

#endif // LOCATIONBYTE_H
