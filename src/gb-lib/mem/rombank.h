#ifndef ROMBANK_H
#define ROMBANK_H

#include "bufferbank.h"

class RomBank final : public BufferBank {
public:
  RomBank(const MemoryArea& area, std::span<uint8_t, std::dynamic_extent> buffer);
  DISABLE_COPY_AND_MOVE(RomBank)

  Location8UP getLocation8(const address_type address) override;
  Location16UP getLocation16(const address_type address) override;
};

#endif // ROMBANK_H
