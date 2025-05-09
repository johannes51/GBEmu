#include "ramlocation.h"

RamLocation::RamLocation(BufferBank& area, address_type start)
    : BufferLocation(area, start)
{
}

auto RamLocation::operator=(const uint8_t& rhs) -> RamLocation&
{
  this->BufferLocation::operator=(rhs);
  return *this;
}
