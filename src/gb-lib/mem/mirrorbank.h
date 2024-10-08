#ifndef MIRRORBANK_H
#define MIRRORBANK_H

#include "singleareamanager.h"

class MirrorBank : public SingleAreaManager {
public:
  MirrorBank(const MemoryArea& mirrorArea, const MemoryArea& originalArea, IMemoryManagerSP mirrored);
  DISABLE_COPY_AND_MOVE(MirrorBank)

  LocationUP getLocation(const address_type address, bool tryWord = false) override;

private:
  const int offset_;
  IMemoryManagerSP mirrored_;
};

#endif // MIRRORBANK_H
