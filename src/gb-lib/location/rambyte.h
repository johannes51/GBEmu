#ifndef RAMLOCATION_H
#define RAMLOCATION_H

#include "bufferbyte.h"

class RamByte final : public BufferByte {
public:
  RamByte(uint8_t &reference);
  DISABLE_COPY_AND_MOVE(RamByte)
};

#endif // RAMLOCATION_H
