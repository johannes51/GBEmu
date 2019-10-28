#ifndef MIRRORBANK_H
#define MIRRORBANK_H

#include "singleareamanager.h"

class MirrorBank : public SingleAreaManager {
public:
  MirrorBank(const MemoryArea& mirrorArea, const MemoryArea& originalArea, IMemoryManagerSP mirrored);
  DISABLE_COPY_AND_MOVE(MirrorBank)

  virtual Location<uint8_t> getByte(const address_type address) override;
  virtual Location<uint16_t> getWord(const address_type address) override;

private:
  const int offset_;
  IMemoryManagerSP mirrored_;
};

#endif // MIRRORBANK_H
