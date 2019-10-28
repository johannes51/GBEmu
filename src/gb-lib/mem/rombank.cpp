#include "rombank.h"

#include "location/location.h"
#include "location/rombyte.h"
#include "mem_tools.h"

RomBank::RomBank(const MemoryArea &area, std::vector<uint8_t>&& buffer)
    : SingleAreaManager(area)
    , buffer_(std::move(buffer))
{
}

Location<uint8_t> RomBank::getByte(address_type address)
{
  return Location<uint8_t>::generate(
      std::make_unique<RomByte>(buffer_.at(mem_tools::translateAdressSafe(address, singleArea()))));
}

Location<uint16_t> RomBank::getWord(address_type address)
{
  return Location<uint16_t>::generate(
      std::make_unique<RomByte>(buffer_[mem_tools::translateAdressSafe(address, singleArea())]),
      std::make_unique<RomByte>(buffer_[mem_tools::translateAdressSafe(address + 1, singleArea())]));
}
