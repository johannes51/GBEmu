#include "singleareamanager.h"

auto SingleAreaManager::availableAreas() -> std::vector<MemoryArea> { return availableAreas_; }

auto SingleAreaManager::singleArea() const -> const MemoryArea& { return availableAreas_.front(); }

SingleAreaManager::SingleAreaManager(const MemoryArea& area)
    : availableAreas_(1)
{
  availableAreas_.front() = area;
}
