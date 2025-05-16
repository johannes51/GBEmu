#include "nullbank.h"

#include "../common/mem_tools.h"
#include "../location8.h"
#include "zerolocation.h"

NullBank::NullBank(const MemoryArea& area)
    : SingleAreaManager(area)
{
}

auto NullBank::getLocation8(const address_type address) -> Location8
{
  mem_tools::assertSafe(address, singleArea());

  return ZeroByteLocation::copy();
}

auto NullBank::getLocation16(const address_type address) -> Location16
{
  mem_tools::assertSafe(address, singleArea());
  mem_tools::assertSafe(address + 1, singleArea());

  return Location16 { ZeroWordLocation::copy() };
}
