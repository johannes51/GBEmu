#include "rambank.h"

#include <stdexcept>

#include "location/fusedlocation16.h"
#include "location/ramlocation.h"
#include "mem_tools.h"

RamBank::RamBank(const MemoryArea& area, std::span<uint8_t, std::dynamic_extent> buffer)
    : BufferBank(area, buffer)
{
}

auto RamBank::getLocation8(const address_type address) -> Location8UP
{
  if (!mem_tools::isSafe(address, singleArea())) {
    throw std::invalid_argument("Out of bounds");
  }
  return std::make_unique<RamLocation>(*this, address);
}

auto RamBank::getLocation16(const address_type address) -> Location16UP
{
  if (!mem_tools::isSafe(address, singleArea()) || !mem_tools::isSafe(address + 1, singleArea())) {
    throw std::invalid_argument("Out of bounds");
  }
  return std::make_unique<FusedLocation16>(
      std::make_unique<RamLocation>(*this, address), std::make_unique<RamLocation>(*this, address + 1U));
}
