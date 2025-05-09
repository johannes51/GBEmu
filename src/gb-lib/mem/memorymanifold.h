#ifndef MEMORYMANIFOLD_H
#define MEMORYMANIFOLD_H

#include <vector>

#include "imemorymanager.h"

class MemoryManifold final : public IMemoryManager {
public:
  MemoryManifold() = default;
  DISABLE_COPY_AND_MOVE(MemoryManifold)

  void addSubManager(const IMemoryManagerSP& newSubManager);

  Location8UP getLocation8(const address_type address) override;
  Location16UP getLocation16(const address_type address) override;

  std::vector<MemoryArea> availableAreas() override;

private:
  IMemoryManagerSP& selectManager(const address_type address);

  std::vector<std::pair<MemoryArea, IMemoryManagerSP>> subManagers_
      = std::vector<std::pair<MemoryArea, IMemoryManagerSP>>();
};

#endif // MEMORYMANIFOLD_H
