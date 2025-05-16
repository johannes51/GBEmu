#ifndef IOBANK_H
#define IOBANK_H

#include "../ram/rambank.h"
#include "memoryregisteradapter.h"

class IoBank : public RamBank {
public:
  explicit IoBank(const MemoryArea& area, std::span<uint8_t, std::dynamic_extent> buffer);

  Location8 getLocation8(const address_type address) override;
  Location16 getLocation16(const address_type address) override;

  virtual ByteLocationAdapterUP getRegisterLocation(const address_type address);
};

#endif // IOBANK_H
