#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include <vector>

#include "cpu/cpu_defines.h"
#include "mem/imemoryview.h"

#include "peripherals/tickable.h"

class SystemManager {
public:
  SystemManager(IMemoryViewSP memory, std::unique_ptr<Cpu> cpu, std::vector<TickableUP> peripherals);
  DISABLE_COPY_AND_MOVE(SystemManager)
  ~SystemManager();

  void clock() const;

private:
  IMemoryViewSP memory_;
  CpuUP cpu_;
  std::vector<TickableUP> peripherals_;
};

#endif // SYSTEMMANAGER_H
