#ifndef MEMORYMANIFOLD_H
#define MEMORYMANIFOLD_H

#include <vector>

#include "imemorymanager.h"

class MemoryManifold final : public IMemoryManager {
public:
  MemoryManifold() = default;
  DISABLE_COPY_AND_MOVE(MemoryManifold)

  void addSubManager(const IMemoryManagerSP& newSubManager);

  LocationUP getLocation(const address_type address, bool tryWord = false) override;

  virtual std::vector<MemoryArea> availableAreas() override;

private:
  IMemoryManagerSP& selectManager(const address_type address);

  std::vector<std::pair<MemoryArea, IMemoryManagerSP>> subManagers_
      = std::vector<std::pair<MemoryArea, IMemoryManagerSP>>();
};

#endif // MEMORYMANIFOLD_H
