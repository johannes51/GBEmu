#include "ramlocation.h"

RamLocation::RamLocation(Type type, BufferBank& area, address_type start)
    : BufferLocation(type, area, start)
{
}

Location& RamLocation::operator=(const uint8_t& rhs)
{
  this->BufferLocation::operator=(rhs);
  return *this;
}

Location& RamLocation::operator=(const uint16_t& rhs)
{
  this->BufferLocation::operator=(rhs);
  return *this;
}
