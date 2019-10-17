#ifndef NULLBYTE_H
#define NULLBYTE_H

#include "locationbyte.h"


class NullByte : public LocationByte
{
public:
  uint8_t operator *();
};

#endif // NULLBYTE_H
