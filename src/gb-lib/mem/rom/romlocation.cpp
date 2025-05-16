#include "romlocation.h"

#include <stdexcept>

RomLocation::RomLocation(uint8_t& buffer)
    : BufferLocation(buffer)
{
}

void RomLocation::set(const uint8_t& value)
{
  (void)value;
  throw std::logic_error("Write on ROM");
}
