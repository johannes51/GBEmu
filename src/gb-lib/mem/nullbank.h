#ifndef NULLBANK_H
#define NULLBANK_H

#include "singleareamanager.h"

class NullBank final : public SingleAreaManager {
public:
  NullBank(const MemoryArea &area);
  DISABLE_COPY_AND_MOVE(NullBank)

  Location<uint8_t> getByte(address_type address) override;
  Location<uint16_t> getWord(address_type address) override;
};

#endif // NULLBANK_H
