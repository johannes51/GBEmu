#ifndef SINGLEAREAMANAGER_H
#define SINGLEAREAMANAGER_H

#include "imemorymanager.h"

class SingleAreaManager : public IMemoryManager {
public:
  SingleAreaManager(MemoryArea area);
  virtual ~SingleAreaManager() = default;
  DISABLE_COPY_AND_MOVE(SingleAreaManager)

  virtual Location<uint8_t> getByte(const address_type address) override = 0;
  virtual Location<uint16_t> getWord(const address_type address) override = 0;
  virtual std::vector<MemoryArea> availableAreas() override;

  const MemoryArea& singleArea() const;

private:
  std::vector<MemoryArea> availableAreas_;
};

#endif // SINGLEAREAMANAGER_H
