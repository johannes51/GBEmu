#include "gbmemory.h"

#include "mem/ramlocation.h"
#include "util/location.h"
#include "util/locationimpl.h"

#include "debug/simplelocation.h"

GBMemory::GBMemory()
{

}

Location<uint8_t>&& GBMemory::getByte(const address_type address)
{
  return Location<uint8_t>::generate(RamLocation(address), SimpleLocation());
}

Location<uint16_t> &&GBMemory::getWord(const address_type address)
{
  return Location<uint16_t>::generate(RamLocation(address), RamLocation(address + 1));
}
