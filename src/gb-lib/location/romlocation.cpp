#include "romlocation.h"

#include <stdexcept>

RomLocation::RomLocation(Type type, BufferBank& area, address_type start)
    : BufferLocation(type, area, start)
{
}

Location& RomLocation::operator=(const uint8_t& rhs)
{
  (void)rhs;
  throw std::logic_error("Write on ROM");
}

Location& RomLocation::operator=(const uint16_t& rhs)
{
  (void)rhs;
  throw std::logic_error("Write on ROM");
}
