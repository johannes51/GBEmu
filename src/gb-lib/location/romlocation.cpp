#include "romlocation.h"

#include <stdexcept>

RomLocation::RomLocation(Type type, BufferBank& area, address_type start)
    : BufferLocation(type, area, start)
{
}

auto RomLocation::operator=(const uint8_t& rhs) -> RomLocation&
{
  (void)rhs;
  throw std::logic_error("Write on ROM");
}

auto RomLocation::operator=(const uint16_t& rhs) -> RomLocation&
{
  (void)rhs;
  throw std::logic_error("Write on ROM");
}
