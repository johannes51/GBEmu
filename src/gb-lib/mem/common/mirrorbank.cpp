#include "mirrorbank.h"

#include <stdexcept>

#include "../ilocation8.h"
#include "mem_tools.h"

MirrorBank::MirrorBank(const MemoryArea& mirrorArea, const MemoryArea& originalArea, IMemoryView& mirrored)
    : SingleAreaView(mirrorArea)
    , offset_(originalArea.from - mirrorArea.from)
    , mirrored_(mirrored)
{
  if (mirrorArea.to - mirrorArea.from > originalArea.to - originalArea.from) {
    throw std::invalid_argument("Mirror bigger than original");
  }
}

auto MirrorBank::getLocation8(const address_type address) -> ILocation8&
{
  return mirrored_.getLocation8(mem_tools::translateAddressSafe(address, area_, offset_));
}
