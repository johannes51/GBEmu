#ifndef ROMLOCATION_H
#define ROMLOCATION_H

#include "bufferlocation.h"

class RomLocation final : public BufferLocation {
public:
  RomLocation(Type type, BufferBank& area, address_type start);
  DISABLE_COPY_AND_MOVE(RomLocation)

  RomLocation& operator=(const uint8_t& rhs) override;
  RomLocation& operator=(const uint16_t& rhs) override;
};

#endif // ROMLOCATION_H
