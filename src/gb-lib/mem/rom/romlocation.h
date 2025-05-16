#ifndef ROMLOCATION_H
#define ROMLOCATION_H

#include "../common/bufferlocation.h"

class RomLocation final : public BufferLocation {
public:
  RomLocation(uint8_t& buffer);
  DISABLE_COPY_AND_MOVE(RomLocation)

  void set(const uint8_t& value) override;
};

#endif // ROMLOCATION_H
