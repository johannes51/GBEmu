#include "registerbyte.h"

RegisterByte::RegisterByte(uint8_t& byte)
  : byte_(byte)
{
}

uint8_t RegisterByte::operator *()
{
  return byte_;
}
