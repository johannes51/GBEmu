#ifndef SINGLEAREAMANAGER_H
#define SINGLEAREAMANAGER_H

#include "../imemorymanager.h"

class SingleAreaManager : public IMemoryManager {
public:
  virtual ~SingleAreaManager() = default;
  DISABLE_COPY_AND_MOVE(SingleAreaManager)

  virtual std::vector<MemoryArea> availableAreas() override;

  const MemoryArea& singleArea() const;

protected:
  SingleAreaManager(const MemoryArea& area);

private:
  std::vector<MemoryArea> availableAreas_; // NOTE: is a vector of length one because of availableAreas()
};

#endif // SINGLEAREAMANAGER_H
