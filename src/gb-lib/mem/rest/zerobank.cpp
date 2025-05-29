#include "zerobank.h"

#include "../common/mem_tools.h"
#include "../ilocation8.h"
#include "zerolocation.h"

ZeroBank::ZeroBank(const MemoryArea& area)
    : SingleAreaView(area)
{
}

auto ZeroBank::getLocation8(const address_type address) -> ILocation8&
{
  mem_tools::assertSafe(address, area_);

  return loc_;
}
