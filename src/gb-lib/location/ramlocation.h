#ifndef RAMLOCATION_H
#define RAMLOCATION_H

#include "bufferlocation.h"

class RamLocation final : public BufferLocation {
public:
  RamLocation(BufferBank& area, address_type start);
  DISABLE_COPY_AND_MOVE(RamLocation)

  RamLocation& operator=(const uint8_t& rhs) override;
};

#endif // RAMLOCATION_H
