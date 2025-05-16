#include "mirrorbank.h"

#include <stdexcept>

#include "../location8.h"
#include "mem_tools.h"

MirrorBank::MirrorBank(const MemoryArea& mirrorArea, const MemoryArea& originalArea, IMemoryManagerSP mirrored)
    : SingleAreaManager(mirrorArea)
    , offset_(originalArea.from - mirrorArea.from)
    , mirrored_(std::move(mirrored))
{
  if (mirrorArea.to - mirrorArea.from > originalArea.to - originalArea.from) {
    throw std::invalid_argument("Mirror bigger than original");
  }
}

auto MirrorBank::getLocation8(const address_type address) -> Location8
{
  return mirrored_->getLocation8(mem_tools::translateAddressSafe(address, singleArea(), offset_));
}

auto MirrorBank::getLocation16(const address_type address) -> Location16
{
  mem_tools::assertSafe(address + 1, singleArea());
  return mirrored_->getLocation16(mem_tools::translateAddressSafe(address, singleArea(), offset_));
}
