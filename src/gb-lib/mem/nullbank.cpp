#include "nullbank.h"

#include "location/location.h"
#include "location/zerobyte.h"
#include "mem_tools.h"

NullBank::NullBank(MemoryArea area)
  : SingleAreaManager(area)
{
}

LocationUP<uint8_t> NullBank::getByte(address_type address)
{
  mem_tools::translateAdressSafe(address, singleArea());
  return Location<uint8_t>::generate(std::make_unique<ZeroByte>());
}

LocationUP<uint16_t> NullBank::getWord(address_type address)
{
  return Location<uint16_t>::generate(std::make_unique<ZeroByte>(), std::make_unique<ZeroByte>());
}