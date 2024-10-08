#ifndef NULLBANK_H
#define NULLBANK_H

#include "singleareamanager.h"

class NullBank final : public SingleAreaManager {
public:
  NullBank(const MemoryArea& area);
  DISABLE_COPY_AND_MOVE(NullBank)

  LocationUP getLocation(const address_type address, bool tryWord = false) override;
};

#endif // NULLBANK_H
