#include "memorymanifold.h"

#include <algorithm>
#include <numeric>
#include <stdexcept>

#include "location/location.h"
#include "mem_tools.h"

void MemoryManifold::addSubManager(const IMemoryManagerSP& newSubManager)
{
  const auto newAreas = newSubManager->availableAreas();
  const auto oldAreas = availableAreas();

  if (!std::accumulate(newAreas.begin(), newAreas.end(), true,
          [oldAreas](auto& a, const auto& b) { return a && mem_tools::isDisjunct(b, oldAreas); })) {
    throw std::invalid_argument("Areas collide");
  }

  std::transform(newAreas.begin(), newAreas.end(), std::back_inserter(subManagers_),
      [newSubManager](const auto& newArea) { return std::make_pair(newArea, newSubManager); });
}

Location<uint8_t> MemoryManifold::getByte(const address_type address)
{
  return selectManager(address)->getByte(address);
}

Location<uint16_t> MemoryManifold::getWord(const address_type address)
{
  return selectManager(address)->getWord(address);
}

std::vector<MemoryArea> MemoryManifold::availableAreas()
{
  std::vector<MemoryArea> result(subManagers_.size());
  std::transform(
      subManagers_.begin(), subManagers_.end(), result.begin(), [](const auto& element) { return element.first; });
  return result;
}

IMemoryManagerSP& MemoryManifold::selectManager(const address_type address)
{
  auto it = std::find_if(subManagers_.begin(), subManagers_.end(),
      [&](const auto& element) { return mem_tools::isSafe(address, element.first); });
  if (it == subManagers_.end()) {
    throw std::invalid_argument("Out of bounds");
  }
  return it->second;
}
