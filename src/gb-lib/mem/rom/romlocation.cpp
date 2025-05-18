#include "romlocation.h"

#include <stdexcept>

RomLocation::RomLocation(uint8_t& buffer)
    : BufferLocation(buffer)
{
}

void RomLocation::set(const uint8_t& value)
{
  (void)value; // TODO: ignore all ROM writes for now, add MBC later.
}
