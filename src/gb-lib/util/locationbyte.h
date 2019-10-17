#ifndef LOCATIONBYTE_H
#define LOCATIONBYTE_H

#include <stdint.h>


class LocationByte
{
public:
  LocationByte();
  virtual ~LocationByte();

  virtual uint8_t operator*() = 0;
};

#endif // LOCATIONBYTE_H
