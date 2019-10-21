#ifndef RAMBANK_H
#define RAMBANK_H

#include "singleareamanager.h"

class RamBank : public SingleAreaManager {
public:
  RamBank(MemoryArea area);
  DISABLE_COPY_AND_MOVE(RamBank)

  LocationUP<uint8_t> getByte(address_type address);
  LocationUP<uint16_t> getWord(address_type address);

private:
  address_type start_;
  address_type size_;
  std::vector<uint8_t> buffer_;
};

#endif // RAMBANK_H
