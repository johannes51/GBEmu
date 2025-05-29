#ifndef ROMLOCATION_H
#define ROMLOCATION_H

#include "../common/bufferlocation.h"

#include "../mem_defines.h"
#include "cart/mbc.h"

class RomLocation final : public BufferLocation {
public:
  RomLocation(uint8_t& buffer);
  DISABLE_COPY_AND_MOVE(RomLocation)

  RomLocation& operator=(const uint8_t& rhs) override;

  void setMbc(Mbc* value);
  void setAddress(const address_type value);

private:
  Mbc* mbc_;
  address_type address_;
};

#endif // ROMLOCATION_H
