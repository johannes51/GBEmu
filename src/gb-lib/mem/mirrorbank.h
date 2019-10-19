#ifndef MIRRORBANK_H
#define MIRRORBANK_H

#include "singleareamanager.h"


class MirrorBank : public SingleAreaManager
{
public:
  MirrorBank(MemoryArea mirrorArea, MemoryArea originalArea, IMemoryManagerSP mirrored);

  LocationUP<uint8_t> getByte(address_type address);
  LocationUP<uint16_t> getWord(address_type address);

private:
  int offset_;
  IMemoryManagerSP mirrored_;
};

#endif // MIRRORBANK_H
