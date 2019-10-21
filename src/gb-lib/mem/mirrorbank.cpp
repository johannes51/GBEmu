#include "mirrorbank.h"

#include "location/location.h"
#include "mem_tools.h"

MirrorBank::MirrorBank(MemoryArea mirrorArea, MemoryArea originalArea,
                       IMemoryManagerSP mirrored)
    : SingleAreaManager(mirrorArea),
      offset_(originalArea.from - mirrorArea.from),
      mirrored_(std::move(mirrored)) {
  if (mirrorArea.to - mirrorArea.from > originalArea.to - originalArea.from) {
    throw std::invalid_argument("Mirror bigger than original");
  }
}

LocationUP<uint8_t> MirrorBank::getByte(address_type address) {
  return mirrored_->getByte(
      mem_tools::translateAdressSafe(address, singleArea(), offset_));
}

LocationUP<uint16_t> MirrorBank::getWord(address_type address) {
  return mirrored_->getWord(
      mem_tools::translateAdressSafe(address, singleArea(), offset_));
}
