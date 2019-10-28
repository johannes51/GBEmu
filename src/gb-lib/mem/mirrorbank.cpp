#include "mirrorbank.h"

#include "location/location.h"
#include "mem_tools.h"

MirrorBank::MirrorBank(const MemoryArea &mirrorArea, const MemoryArea &originalArea, IMemoryManagerSP mirrored)
    : SingleAreaManager(mirrorArea)
    , offset_(originalArea.from - mirrorArea.from)
    , mirrored_(std::move(mirrored))
{
  if (mirrorArea.to - mirrorArea.from > originalArea.to - originalArea.from) {
    throw std::invalid_argument("Mirror bigger than original");
  }
}

Location<uint8_t> MirrorBank::getByte(address_type address)
{
  return mirrored_->getByte(mem_tools::translateAdressSafe(address, singleArea(), offset_));
}

Location<uint16_t> MirrorBank::getWord(address_type address)
{
  mem_tools::assertSafe(address + 1, singleArea());
  return mirrored_->getWord(mem_tools::translateAdressSafe(address, singleArea(), offset_));
}
