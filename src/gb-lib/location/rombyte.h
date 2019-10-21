#ifndef ROMBYTE_H
#define ROMBYTE_H

#include "bufferbyte.h"

class RomByte : public BufferByte {
public:
  RomByte(uint8_t &reference);

  virtual LocationByte &operator<<(const uint8_t &value) override;
};

#endif // ROMBYTE_H
