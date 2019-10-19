#include "bufferbyte.h"


BufferByte::BufferByte(uint8_t& reference)
  : reference_(reference)
{
}

uint8_t BufferByte::operator *()
{
  return reference_;
}

LocationByte& BufferByte::operator <<(const uint8_t& value)
{
  reference_ = value;
  return *this;
}

