#ifndef GBMEMORY_H
#define GBMEMORY_H

#include "memoryview.h"


class GBMemory : public MemoryView
{
public:
  GBMemory();

  Location<uint8_t> getByte(const address_type address);
  Location<uint16_t> getWord(const address_type address);

private:
  std::array<uint8_t, 0xFFFF> ram_;
};

#endif // GBMEMORY_H
