#include "mirrorbank.h"

#include <stdexcept>

#include "location/location.h"
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

auto MirrorBank::getByte(address_type address) -> Location<uint8_t>
{
  return mirrored_->getByte(mem_tools::translateAddressSafe(address, singleArea(), offset_));
}

auto MirrorBank::getWord(address_type address) -> Location<uint16_t>
{
  mem_tools::assertSafe(address + 1, singleArea());
  return mirrored_->getWord(mem_tools::translateAddressSafe(address, singleArea(), offset_));
}
