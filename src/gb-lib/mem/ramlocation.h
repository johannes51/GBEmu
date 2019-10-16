#ifndef RAMLOCATION_H
#define RAMLOCATION_H

#include "util/locationbyte.h"
#include "mem/mem_defines.h"


class RamLocation : public LocationByte
{
public:
  RamLocation(address_type adress);
};

#endif // RAMLOCATION_H
