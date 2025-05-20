#ifndef MIRRORBANK_H
#define MIRRORBANK_H

#include "singleareamanager.h"

class MirrorBank : public SingleAreaManager {
public:
  MirrorBank(const MemoryArea& mirrorArea, const MemoryArea& originalArea, IMemoryManager& mirrored);
  DISABLE_COPY_AND_MOVE(MirrorBank)

  Location8 getLocation8(const address_type address) override;
  Location16 getLocation16(const address_type address) override;

private:
  const int offset_;
  IMemoryManager& mirrored_;
};

#endif // MIRRORBANK_H
