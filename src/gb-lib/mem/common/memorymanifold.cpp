#include "memorymanifold.h"

#include <algorithm>
#include <numeric>
#include <stdexcept>

#include "../location8.h"
#include "mem_tools.h"

void MemoryManifold::addSubManager(IMemoryManagerUP newSubManager)
{
  auto* newSubManagerP = newSubManager.get();
  subManagersHold_.emplace_back(std::move(newSubManager));

  const auto newAreas = newSubManagerP->availableAreas();
  const auto oldAreas = availableAreas();

  if (!std::accumulate(newAreas.begin(), newAreas.end(), true,
          [oldAreas](const auto& a, const auto& b) { return a && mem_tools::isDisjunct(b, oldAreas); })) {
    throw std::invalid_argument("Areas collide");
  }

  for (const auto& newArea : newAreas) {
    auto pair = std::make_pair(newArea, newSubManagerP);
    subManagersMap_.emplace_back(std::move(pair));
  }
}

auto MemoryManifold::getLocation8(const address_type address) -> Location8
{
  return selectManager(address).getLocation8(address);
}

auto MemoryManifold::getLocation16(const address_type address) -> Location16
{
  return selectManager(address).getLocation16(address);
}

auto MemoryManifold::availableAreas() -> std::vector<MemoryArea>
{
  std::vector<MemoryArea> result(subManagersMap_.size());
  std::transform(subManagersMap_.begin(), subManagersMap_.end(), result.begin(),
      [](const auto& element) { return element.first; });
  return result;
}

auto MemoryManifold::selectManager(const address_type address) -> IMemoryManager&
{
  auto it = std::find_if(subManagersMap_.begin(), subManagersMap_.end(),
      [&](const auto& element) { return mem_tools::isSafe(address, element.first); });
  if (it == subManagersMap_.end()) {
    throw std::invalid_argument("Out of bounds");
  }
  return *it->second;
}
