#include "singleareamanager.h"

const std::vector<MemoryArea>& SingleAreaManager::availableAreas()
{
  return availableAreas_;
}

const MemoryArea &SingleAreaManager::singleArea() const
{
  return availableAreas_.front();
}

SingleAreaManager::SingleAreaManager(MemoryArea area)
{
  availableAreas_.push_back(area);
}
