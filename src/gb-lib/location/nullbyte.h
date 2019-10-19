#ifndef NULLBYTE_H
#define NULLBYTE_H

#include "locationbyte.h"


class NullByte : public LocationByte
{
public:
  uint8_t operator *();
  NullByte& operator <<(const uint8_t& value);
};

#endif // NULLBYTE_H
