#ifndef SINGLEAREAMANAGER_H
#define SINGLEAREAMANAGER_H

#include "imemorymanager.h"


class SingleAreaManager : public IMemoryManager
{
public:
  const std::vector<MemoryArea>& availableAreas();

  const MemoryArea& singleArea() const;

protected:
  SingleAreaManager(MemoryArea area);

private:
  std::vector<MemoryArea> availableAreas_;
};

#endif // SINGLEAREAMANAGER_H