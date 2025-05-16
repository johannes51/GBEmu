#include "rombank.h"

#include "../common/mem_tools.h"
#include "mem/common/fusedlocation16.h"
#include "romlocation.h"

RomBank::RomBank(const MemoryArea& area, std::span<uint8_t, std::dynamic_extent> buffer)
    : BufferBank(area, buffer)
{
}

auto RomBank::getLocation8(const address_type address) -> Location8
{
  if (!mem_tools::isSafe(address, singleArea())) {
    throw std::invalid_argument("Out of bounds");
  }
  return { std::make_unique<RomLocation>(this->getByteReference(address)) };
}

auto RomBank::getLocation16(const address_type address) -> Location16
{
  if (!mem_tools::isSafe(address, singleArea()) || !mem_tools::isSafe(address + 1, singleArea())) {
    throw std::invalid_argument("Out of bounds");
  }
  return { std::make_unique<FusedLocation16>(
      std::make_unique<Location8>(std::make_unique<RomLocation>(this->getByteReference(address))),
      std::make_unique<Location8>((std::make_unique<RomLocation>(this->getByteReference(address + 1U))))) };
}
