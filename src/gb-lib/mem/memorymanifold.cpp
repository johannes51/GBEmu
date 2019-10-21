#include "memorymanifold.h"

#include "location/location.h"


MemoryManifold::MemoryManifold()
  : subManagers_()
{
}

void MemoryManifold::addSubManager(IMemoryManagerSP newSubManager)
{
  auto areas = newSubManager->availableAreas();
  for (auto area : areas) {
    subManagers_[area] = newSubManager;
  }
}

LocationUP<uint8_t> MemoryManifold::getByte(address_type address)
{
  for (auto areaAndManager : subManagers_) {
    if (areaAndManager.first.from <= address && areaAndManager.first.to >= address) {
      return areaAndManager.second->getByte(address);
    }
  };
  throw std::invalid_argument("Out of bounds");
}

LocationUP<uint16_t> MemoryManifold::getWord(address_type address)
{
  for (auto areaAndManager : subManagers_) {
    if (areaAndManager.first.from <= address && areaAndManager.first.to - 1 >= address) {
      return areaAndManager.second->getWord(address);
    }
  };
  throw std::invalid_argument("Out of bounds");
}

const std::vector<MemoryArea>& MemoryManifold::availableAreas()
{
  throw false;
}

