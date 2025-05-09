#ifndef RAMBANK_H
#define RAMBANK_H

#include "bufferbank.h"

class RamBank : public BufferBank {
public:
  RamBank(const MemoryArea& area, std::span<uint8_t, std::dynamic_extent> buffer);
  DISABLE_COPY_AND_MOVE(RamBank)

  Location8UP getLocation8(const address_type address) override;
  Location16UP getLocation16(const address_type address) override;

private:
  address_type start_;
  address_type size_;
};

#endif // RAMBANK_H
