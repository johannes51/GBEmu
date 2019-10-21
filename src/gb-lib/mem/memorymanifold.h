#ifndef MEMORYMANIFOLD_H
#define MEMORYMANIFOLD_H

#include <map>

#include "imemorymanager.h"

class MemoryManifold : public IMemoryManager {
public:
  MemoryManifold();
  ~MemoryManifold() = default;

  void addSubManager(const IMemoryManagerSP &newSubManager);

  LocationUP<uint8_t> getByte(address_type address);
  LocationUP<uint16_t> getWord(address_type address);
  const std::vector<MemoryArea> &availableAreas();

private:
  std::map<MemoryArea, IMemoryManagerSP> subManagers_;
};

#endif // MEMORYMANIFOLD_H
