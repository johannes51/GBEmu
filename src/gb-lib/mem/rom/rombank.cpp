#include "rombank.h"

#include "../common/mem_tools.h"

RomBank::RomBank(const MemoryArea& area, std::span<uint8_t, std::dynamic_extent> buffer)
    : BufferBank(area, buffer)
    , loc_(buffer_[0U])
{
}

auto RomBank::getLocation8(const address_type address) -> ILocation8&
{
  loc_.setBuffer(buffer_[mem_tools::translateAddressSafe(address, area_)]);
  loc_.setAddress(address);
  return loc_;
}

void RomBank::setMbc(Mbc* value) { loc_.setMbc(value); }
