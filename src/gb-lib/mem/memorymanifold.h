#ifndef MEMORYMANIFOLD_H
#define MEMORYMANIFOLD_H

#include <vector>

#include "imemorymanager.h"

class MemoryManifold final : public IMemoryManager {
public:
  MemoryManifold();
  DISABLE_COPY_AND_MOVE(MemoryManifold)

  void addSubManager(const IMemoryManagerSP &newSubManager);

  Location<uint8_t> getByte(const address_type address) override;
  Location<uint16_t> getWord(const address_type address) override;
  virtual std::vector<MemoryArea> availableAreas() override;

private:
  IMemoryManagerSP &selectManager(const address_type address);

  std::vector<std::pair<MemoryArea, IMemoryManagerSP>> subManagers_;
};

#endif // MEMORYMANIFOLD_H
