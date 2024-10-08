#include "nullbank.h"

#include "location/location.h"
#include "location/zerolocation.h"
#include "mem_tools.h"

NullBank::NullBank(const MemoryArea& area)
    : SingleAreaManager(area)
{
}

auto NullBank::getLocation(const address_type address, bool tryWord) -> LocationUP
{
  mem_tools::assertSafe(address, singleArea());
  if (tryWord) {
    mem_tools::assertSafe(address + 1, singleArea());
  }
  return std::make_unique<ZeroLocation>();
}
