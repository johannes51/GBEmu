#ifndef IMEMORYMANAGER_H
#define IMEMORYMANAGER_H

#include <vector>

#include "imemoryview.h"
#include "memoryarea.h"

class IMemoryManager : public IMemoryView {
public:
  IMemoryManager() = default;
  virtual ~IMemoryManager() = default;
  DISABLE_COPY_AND_MOVE(IMemoryManager)

  virtual std::vector<MemoryArea> availableAreas() = 0;
};

#endif // IMEMORYMANAGER_H
