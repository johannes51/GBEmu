#ifndef SIMPLELOCATION_H
#define SIMPLELOCATION_H

#include "location/locationbyte.h"


class SimpleLocation : public LocationByte
{
public:
  SimpleLocation();

  uint8_t operator *();
  SimpleLocation& operator <<(const uint8_t& value);
};

#endif // SIMPLELOCATION_H
