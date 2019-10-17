#ifndef SIMPLELOCATION_H
#define SIMPLELOCATION_H

#include "util/locationbyte.h"


class SimpleLocation : public LocationByte
{
public:
  SimpleLocation();

  uint8_t operator *();
};

#endif // SIMPLELOCATION_H
