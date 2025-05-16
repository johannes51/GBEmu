#ifndef RAMLOCATION_H
#define RAMLOCATION_H

#include "../common/bufferlocation.h"

class RamLocation final : public BufferLocation {
public:
  RamLocation(uint8_t& buffer);
  DISABLE_COPY_AND_MOVE(RamLocation)
};

#endif // RAMLOCATION_H
