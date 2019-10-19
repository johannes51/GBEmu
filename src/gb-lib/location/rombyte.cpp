#include "rombyte.h"

#include <stdexcept>

RomByte::RomByte(uint8_t& reference)
  : BufferByte(reference)
{
}

LocationByte& RomByte::operator <<(const uint8_t& value)
{
  throw std::logic_error("Write on ROM");
}
