#include "rombank.h"

#include "location/location.h"
#include "location/romlocation.h"
#include "mem_tools.h"

RomBank::RomBank(const MemoryArea& area, std::span<uint8_t, std::dynamic_extent> buffer)
    : BufferBank(area, std::move(buffer))
{
}

LocationUP RomBank::getLocation(const address_type address, bool tryWord)
{
  return std::make_unique<RomLocation>(
      tryWord && mem_tools::isSafe(address + 1, singleArea()) ? Location::Type::Both : Location::Type::Single, *this,
      address);
}
