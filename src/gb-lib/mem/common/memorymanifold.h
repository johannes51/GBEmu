#ifndef MEMORYMANIFOLD_H
#define MEMORYMANIFOLD_H

#include <vector>

#include "../imemorymanager.h"

class MemoryManifold final : public IMemoryManager {
public:
  MemoryManifold() = default;
  DISABLE_COPY_AND_MOVE(MemoryManifold)

  void addSubManager(IMemoryManagerUP newSubManager);

  Location8 getLocation8(const address_type address) override;
  Location16 getLocation16(const address_type address) override;

  std::vector<MemoryArea> availableAreas() override;

private:
  IMemoryManager& selectManager(const address_type address);

  std::vector<std::pair<MemoryArea, IMemoryManager*>> subManagersMap_
      = std::vector<std::pair<MemoryArea, IMemoryManager*>>();
  std::vector<IMemoryManagerUP> subManagersHold_;
};

#endif // MEMORYMANIFOLD_H
