#ifndef RAMBANK_H
#define RAMBANK_H

#include "../common/bufferbank.h"

#include <span>

#include "../mem_defines.h"
#include "ramlocation.h"

class RamBank : public BufferBank {
public:
  RamBank(const MemoryArea& area, std::span<uint8_t, std::dynamic_extent> buffer);
  DISABLE_COPY_AND_MOVE(RamBank)

  ILocation8& getLocation8(const address_type address) override;

private:
  RamLocation loc_;
};

#endif // RAMBANK_H
