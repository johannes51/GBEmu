#include "ramlocation.h"

RamLocation::RamLocation(uint8_t& buffer)
    : BufferLocation(buffer)
{
}

auto RamLocation::operator=(const uint8_t& rhs) -> RamLocation&
{
  BufferLocation::operator=(rhs);
  return *this;
}
