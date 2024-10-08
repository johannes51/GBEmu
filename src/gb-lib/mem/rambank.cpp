#include "rambank.h"

#include <stdexcept>

#include "location/ramlocation.h"
#include "mem_tools.h"

RamBank::RamBank(const MemoryArea& area, std::span<uint8_t, std::dynamic_extent> buffer)
    : BufferBank(area, std::move(buffer))
    , start_(area.from)
    , size_(area.to - area.from + 1)
{
}

LocationUP RamBank::getLocation(const address_type address, bool tryWord)
{
  if (!mem_tools::isSafe(address, singleArea())) {
    throw std::invalid_argument("Out of bounds");
  }
  if (tryWord && !mem_tools::isSafe(address + 1, singleArea())) {
    throw std::invalid_argument("Out of bounds");
  }
  return std::make_unique<RamLocation>(
      tryWord && mem_tools::isSafe(address + 1, singleArea()) ? Location::Type::Both : Location::Type::Single, *this,
      address);
}
