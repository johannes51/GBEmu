#ifndef ROMBYTE_H
#define ROMBYTE_H

#include "bufferbyte.h"

class RomByte final : public BufferByte {
public:
  RomByte(uint8_t& reference);

  void set(const uint8_t& value) override;
};

#endif // ROMBYTE_H
