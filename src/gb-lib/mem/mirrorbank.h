#ifndef MIRRORBANK_H
#define MIRRORBANK_H

#include "singleareamanager.h"

class MirrorBank : public SingleAreaManager {
public:
  MirrorBank(MemoryArea mirrorArea, MemoryArea originalArea,
             IMemoryManagerSP mirrored);

  virtual LocationUP<uint8_t> getByte(const address_type address) override;
  virtual LocationUP<uint16_t> getWord(const address_type address) override;

private:
  int offset_;
  IMemoryManagerSP mirrored_;
};

#endif // MIRRORBANK_H
