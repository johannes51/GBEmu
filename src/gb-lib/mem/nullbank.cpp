#include "nullbank.h"

#include "location/location8.h"
#include "location/zerolocation.h"
#include "mem_tools.h"

NullBank::NullBank(const MemoryArea& area)
    : SingleAreaManager(area)
{
}

auto NullBank::getLocation8(const address_type address) -> Location8UP
{
  mem_tools::assertSafe(address, singleArea());

  return std::make_unique<ZeroLocation8>();
}

auto NullBank::getLocation16(const address_type address) -> Location16UP
{
  mem_tools::assertSafe(address, singleArea());
  mem_tools::assertSafe(address + 1, singleArea());

  return std::make_unique<ZeroLocation16>();
}
