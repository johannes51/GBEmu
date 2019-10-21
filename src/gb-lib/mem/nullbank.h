#ifndef NULLBANK_H
#define NULLBANK_H

#include "singleareamanager.h"

class NullBank : public SingleAreaManager {
public:
  NullBank(MemoryArea area);
  DISABLE_COPY_AND_MOVE(NullBank)

  LocationUP<uint8_t> getByte(address_type address);
  LocationUP<uint16_t> getWord(address_type address);
};

#endif // NULLBANK_H
