#include "romlocation.h"

#include <stdexcept>

RomLocation::RomLocation(BufferBank& area, address_type start)
    : BufferLocation(area, start)
{
}

auto RomLocation::operator=(const uint8_t& rhs) -> RomLocation&
{
  (void)rhs;
  throw std::logic_error("Write on ROM");
}
