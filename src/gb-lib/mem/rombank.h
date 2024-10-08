#ifndef ROMBANK_H
#define ROMBANK_H

#include "bufferbank.h"

class RomBank final : public BufferBank {
public:
  RomBank(const MemoryArea& area, std::span<uint8_t, std::dynamic_extent> buffer);
  DISABLE_COPY_AND_MOVE(RomBank)

  LocationUP getLocation(const address_type address, bool tryWord = false) override;
};

#endif // ROMBANK_H
