#ifndef NULLBANK_H
#define NULLBANK_H

#include "../common/singleareamanager.h"

class NullBank final : public SingleAreaManager {
public:
  NullBank(const MemoryArea& area);
  DISABLE_COPY_AND_MOVE(NullBank)

  Location8 getLocation8(const address_type address) override;
  Location16 getLocation16(const address_type address) override;
};

#endif // NULLBANK_H
