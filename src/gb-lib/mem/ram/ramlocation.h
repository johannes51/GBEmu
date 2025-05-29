#ifndef RAMLOCATION_H
#define RAMLOCATION_H

#include "../common/bufferlocation.h"

class RamLocation final : public BufferLocation {
public:
  explicit RamLocation(uint8_t& buffer);
  DISABLE_COPY_AND_MOVE(RamLocation)

  RamLocation& operator=(const uint8_t& rhs) override;
};

#endif // RAMLOCATION_H
