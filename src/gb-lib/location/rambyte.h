#ifndef RAMLOCATION_H
#define RAMLOCATION_H

#include "bufferbyte.h"

class RamByte final : public BufferByte {
public:
  RamByte(uint8_t &reference);
};

#endif // RAMLOCATION_H
