#ifndef IMEMORYMANAGER_H
#define IMEMORYMANAGER_H

#include <stdint.h>
#include <vector>
#include <stdexcept>

#include "imemoryview.h"
#include "mem_defines.h"


class IMemoryManager : public IMemoryView
{
public:
  virtual ~IMemoryManager() = default;

  virtual const std::vector<MemoryArea>& availableAreas() = 0;
};

#endif // IMEMORYMANAGER_H