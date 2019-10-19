#ifndef ZEROBYTE_H
#define ZEROBYTE_H

#include "locationbyte.h"


class ZeroByte : public LocationByte
{
public:
  uint8_t operator *();
  LocationByte& operator <<(const uint8_t &value);
};

#endif // ZEROBYTE_H