#include "memorymanifold.h"

#include <algorithm>
#include <numeric>

#include "location/location.h"
#include "mem_tools.h"

MemoryManifold::MemoryManifold() : subManagers_() {}

void MemoryManifold::addSubManager(const IMemoryManagerSP &newSubManager) {
  auto makeAreaManagerPair = [newSubManager](const auto &element) {
    return std::make_pair(element, newSubManager);
  };
  auto newAreas = newSubManager->availableAreas();
  auto oldAreas = availableAreas();

  if (!std::accumulate(newAreas.begin(), newAreas.end(), true,
                       [oldAreas](auto &a, const auto &b) {
                         return a && mem_tools::isDisjunct(b, oldAreas);
                       })) {
    throw std::invalid_argument("Areas collide");
  }

  std::transform(newAreas.begin(), newAreas.end(),
                 std::back_inserter(subManagers_), makeAreaManagerPair);
}

LocationUP<uint8_t> MemoryManifold::getByte(const address_type address) {
  return selectManager(address)->getByte(address);
}

LocationUP<uint16_t> MemoryManifold::getWord(const address_type address) {
  return selectManager(address)->getWord(address);
}

std::vector<MemoryArea> MemoryManifold::availableAreas() {
  std::vector<MemoryArea> result(subManagers_.size());
  std::transform(subManagers_.begin(), subManagers_.end(), result.begin(),
                 [](const auto &element) { return element.first; });
  return result;
}

IMemoryManagerSP &MemoryManifold::selectManager(const address_type address) {
  auto checkInArea = [&](const auto &element) {
    return mem_tools::isSafe(address, element.first);
  };
  auto it = std::find_if(subManagers_.begin(), subManagers_.end(), checkInArea);
  if (it == subManagers_.end()) {
    throw std::invalid_argument("Out of bounds");
  }
  return it->second;
}
