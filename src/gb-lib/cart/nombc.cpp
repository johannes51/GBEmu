#include "nombc.h"

#include "mem/common/mem_tools.h"
#include "mem/rest/onelocation.h"

NoMbc::NoMbc(IMemoryViewUP rom0, IMemoryViewUP rom1)
    : rom0_(std::move(rom0))
    , rom1_(std::move(rom1))
{
}

auto NoMbc::getLocation8(const address_type address) -> ILocation8&
{
  if (address <= Rom0Area.to) {
    return rom0_->getLocation8(address);
  } else if (address <= Rom1Area.to) {
    return rom1_->getLocation8(address);
  } else if (mem_tools::isSafe(address, ExtRamArea)) {
    return OneLocation::instance();
  } else {
    throw std::logic_error { "Non-cart address sent to MBC: " + std::to_string(address) };
  }
}

void NoMbc::handleWrite(const address_type address, const uint8_t value)
{
  (void)address;
  (void)value;
}
