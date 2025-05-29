#include "rambank.h"

#include <stdexcept>

#include "../common/mem_tools.h"
#include "mem/common/fusedlocation16.h"
#include "ramlocation.h"

RamBank::RamBank(const MemoryArea& area, std::span<uint8_t, std::dynamic_extent> buffer)
    : BufferBank(area, buffer)
    , loc_(buffer_[0U])
{
}

auto RamBank::getLocation8(const address_type address) -> ILocation8&
{
  loc_.setBuffer(buffer_[mem_tools::translateAddressSafe(address, area_)]);
  return loc_;
}
