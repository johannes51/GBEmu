#include "ramlocation.h"

RamLocation::RamLocation(Type type, BufferBank& area, address_type start)
    : BufferLocation(type, area, start)
{
}

auto RamLocation::operator=(const uint8_t& rhs) -> RamLocation&
{
  this->BufferLocation::operator=(rhs);
  return *this;
}

auto RamLocation::operator=(const uint16_t& rhs) -> RamLocation&
{
  this->BufferLocation::operator=(rhs);
  return *this;
}
