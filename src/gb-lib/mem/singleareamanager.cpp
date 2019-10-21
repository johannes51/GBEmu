#include "singleareamanager.h"

std::vector<MemoryArea> SingleAreaManager::availableAreas() {
  return availableAreas_;
}

const MemoryArea &SingleAreaManager::singleArea() const {
  return availableAreas_.front();
}

SingleAreaManager::SingleAreaManager(MemoryArea area) : availableAreas_(1) {
  availableAreas_.front() = area;
}
