#ifndef RAMBANK_H
#define RAMBANK_H

#include "bufferbank.h"

class RamBank : public BufferBank {
public:
  RamBank(const MemoryArea& area, std::span<uint8_t, std::dynamic_extent> buffer);
  DISABLE_COPY_AND_MOVE(RamBank)

  LocationUP getLocation(const address_type address, bool tryWord = false) override;

private:
  address_type start_;
  address_type size_;
};

#endif // RAMBANK_H
