#ifndef ROMBYTE_H
#define ROMBYTE_H

#include "bufferbyte.h"


class RomByte : public BufferByte
{
public:
  RomByte(uint8_t &reference);
};

#endif // ROMBYTE_H
