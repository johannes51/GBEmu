#include "mirrorbank.h"

#include "location/location.h"
#include "mem_tools.h"

MirrorBank::MirrorBank(MemoryArea mirrorArea, MemoryArea originalArea,
                       IMemoryManagerSP mirrored)
    : SingleAreaManager(mirrorArea), mirrored_(mirrored),
      offset_(originalArea.from - mirrorArea.from) {
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
