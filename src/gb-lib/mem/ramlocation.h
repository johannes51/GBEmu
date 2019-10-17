#ifndef RAMLOCATION_H
#define RAMLOCATION_H

#include "util/locationbyte.h"
#include "mem/mem_defines.h"


class RamLocation : public LocationByte
{
public:
  RamLocation(address_type adress);

  uint8_t operator *();
};

#endif // RAMLOCATION_H
