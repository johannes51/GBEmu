#include "rambank.h"

#include <stdexcept>

#include "../common/mem_tools.h"
#include "mem/common/fusedlocation16.h"
#include "ramlocation.h"

RamBank::RamBank(const MemoryArea& area, std::span<uint8_t, std::dynamic_extent> buffer)
    : BufferBank(area, buffer)
{
}

auto RamBank::getLocation8(const address_type address) -> Location8
{
  if (!mem_tools::isSafe(address, singleArea())) {
    throw std::invalid_argument("Out of bounds");
  }
  return { std::make_unique<RamLocation>(getByteReference(address)) };
}

auto RamBank::getLocation16(const address_type address) -> Location16
{
  if (!mem_tools::isSafe(address, singleArea()) || !mem_tools::isSafe(address + 1, singleArea())) {
    throw std::invalid_argument("Out of bounds");
  }
  return { FusedLocation16::construct({std::make_unique<RamLocation>(getByteReference(address))},
      {std::make_unique<RamLocation>(getByteReference(address + 1U))}) };
}
